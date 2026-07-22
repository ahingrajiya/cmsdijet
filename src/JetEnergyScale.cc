#include "../interface/JetEnergyScale.h"

JetEnergyScale::JetEnergyScale()
{
}

JetEnergyScale::~JetEnergyScale()
{
}

void JetEnergyScale::init()
{
    file_input = TFile::Open(fInputLocation.data(), "READ");
    if (fPtBins.size() < 1)
    {
        std::runtime_error("Pt Bins are not set");
    }
    if (fEtaBins.size() < 1)
    {
        std::runtime_error("Eta Bins are not set");
    }
}

void JetEnergyScale::loadHistograms(TFile* f)
{
    if (f->GetDirectory("Jets"))
    {
        gDirectory->GetObject("hRefJES_W", hPtJES);
        if (!hPtJES)
        {
            std::cerr << "pT JES Histogram does not exist. Check the file." << std::endl;
        }
        gDirectory->GetObject("hRefJES_Eta_W", hEtaJES);
        if (!hEtaJES)
        {
            std::cerr << "Eta JES Histogram does not exist. Check the file." << std::endl;
        }
    }
}

std::tuple<TGraphErrors*, TGraphErrors*, TGraphErrors*> JetEnergyScale::fitJetPtResponseCustomBins(TH2D* h2d, const std::vector<double>& pt_bins,
                                                                                                   TDirectory* out_dir = nullptr)
{
    TGraphErrors* gr_response = new TGraphErrors();
    gr_response->SetTitle("Jet Energy Response;Gen Jet pT;Reco pT / Gen pT Mean");

    TGraphErrors* gr_resolution = new TGraphErrors();
    gr_resolution->SetTitle("Jet Energy Resolution;Gen Jet pT;#sigma / Mean");

    TGraphErrors* gr_chi2 = new TGraphErrors();
    gr_chi2->SetTitle("Fit Quality;Gen Jet p_{T} [GeV];#chi^{2} / ndf");

    // Loop over the custom bins (number of bins is size - 1)
    for (size_t i = 0; i < pt_bins.size() - 1; ++i)
    {
        double pt_low = pt_bins[i];
        double pt_high = pt_bins[i + 1];

        // 1. Calculate the center and width of your custom bin for the TGraph
        double gen_pt_center = (pt_high + pt_low) / 2.0;
        double gen_pt_width = (pt_high - pt_low);

        // 2. Find the corresponding X-axis bins in the 2D histogram
        int bin_start = h2d->GetXaxis()->FindBin(pt_low);
        // Subtract a tiny amount from pt_high so we don't accidentally include the next bin boundary
        int bin_end = h2d->GetXaxis()->FindBin(pt_high - 0.0001);

        // Safety check in case the custom bins fall outside the histogram
        if (bin_start > bin_end) continue;

        // 3. Project the Y-axis across the range of X bins
        TString h1d_name = TString::Format("proj_y_custom_bin_%zu", i);
        TH1D* h1d = h2d->ProjectionY(h1d_name, bin_start, bin_end);
        h2d->Draw();

        // Skip if there isn't enough data in this custom bin to fit
        if (h1d->GetEntries() < 15)
        {
            delete h1d;
            continue;
        }

        // 4. Define and initialize the custom Gaussian
        double fit_min = h1d->GetXaxis()->GetXmin();
        double fit_max = h1d->GetXaxis()->GetXmax();

        TString func_name = TString::Format("custom_gaus_%zu", i);
        TF1* custom_gaus = new TF1(func_name, "[0]*TMath::Exp(-0.5*TMath::Power((x-[1])/[2], 2))", fit_min, fit_max);

        custom_gaus->SetParNames("Amplitude", "Mean", "Sigma");
        custom_gaus->SetParameters(h1d->GetMaximum(), h1d->GetMean(), h1d->GetRMS());

        // 5. Perform the fit
        TFitResultPtr fit_result = h1d->Fit(custom_gaus, "QRS");

        // 6. Extract results
        if (fit_result == 0)
        {
            double chi2 = fit_result->Chi2();
            double ndf = fit_result->Ndf();
            double chi2_ndf = (ndf > 0) ? chi2 / ndf : 0;

            double fit_mean = custom_gaus->GetParameter(1);
            double fit_mean_err = custom_gaus->GetParError(1);

            double fit_sigma = custom_gaus->GetParameter(2);
            double fit_sigma_err = custom_gaus->GetParError(2);

            int idx = gr_response->GetN();

            // Store Response
            gr_response->SetPoint(idx, gen_pt_center, fit_mean);
            gr_response->SetPointError(idx, gen_pt_width / 2.0, fit_mean_err);

            // Store Resolution
            if (fit_mean != 0)
            {
                double resolution = fit_sigma / fit_mean;
                double resolution_err = resolution * TMath::Sqrt(TMath::Power(fit_sigma_err / fit_sigma, 2) + TMath::Power(fit_mean_err / fit_mean, 2));

                gr_resolution->SetPoint(idx, gen_pt_center, resolution);
                gr_resolution->SetPointError(idx, gen_pt_width / 2.0, resolution_err);
            }
            gr_chi2->SetPoint(idx, gen_pt_center, chi2_ndf);
            gr_chi2->SetPointError(idx, gen_pt_width / 2.0, 0);
        }

        if (out_dir)
        {
            out_dir->cd();
            h1d->Write();
        }

        // Clean up memory
        delete custom_gaus;
        delete h1d;
    }
    if (out_dir)
    {
        gr_resolution->Write();
        gr_response->Write();
        gr_chi2->Write();
    }

    return std::make_tuple(gr_response, gr_resolution, gr_chi2);
}

std::tuple<TGraphErrors*, TGraphErrors*, TGraphErrors*> JetEnergyScale::fitJetEtaResponseCustomBins(TH2D* h2d_eta, const std::vector<double>& eta_bins,
                                                                                                    TDirectory* out_dir = nullptr)
{
    TGraphErrors* gr_response = new TGraphErrors();
    gr_response->SetTitle("Jet Energy Scale vs #eta;Gen Jet #eta;#LT Reco p_{T} / Gen p_{T} #GT");

    TGraphErrors* gr_resolution = new TGraphErrors();
    gr_resolution->SetTitle("Jet Energy Resolution vs #eta;Gen Jet #eta;#sigma / #LT Reco p_{T} / Gen p_{T} #GT");

    TGraphErrors* gr_chi2 = new TGraphErrors();
    gr_chi2->SetTitle("Fit Quality vs #eta;Gen Jet #eta;#chi^{2} / ndf");

    for (size_t i = 0; i < eta_bins.size() - 1; ++i)
    {
        double eta_low = eta_bins[i];
        double eta_high = eta_bins[i + 1];

        double gen_eta_center = (eta_high + eta_low) / 2.0;
        double gen_eta_width = (eta_high - eta_low);

        int bin_start = h2d_eta->GetXaxis()->FindBin(eta_low);
        // Ensure we don't double-count boundaries
        int bin_end = h2d_eta->GetXaxis()->FindBin(eta_high - 0.0001);

        if (bin_start > bin_end) continue;

        // Use _plus_ and _minus_ strings to keep ROOT object names clean from negative signs
        TString eta_low_str = TString::Format("%.2f", eta_low).ReplaceAll("-", "minus_");
        TString eta_high_str = TString::Format("%.2f", eta_high).ReplaceAll("-", "minus_");

        TString h1d_name = TString::Format("proj_y_eta_bin_%zu_%s_to_%s", i, eta_low_str.Data(), eta_high_str.Data());
        TH1D* h1d = h2d_eta->ProjectionY(h1d_name, bin_start, bin_end);

        if (h1d->GetEntries() < 15)
        {
            delete h1d;
            continue;
        }

        double fit_min = h1d->GetXaxis()->GetXmin();
        double fit_max = h1d->GetXaxis()->GetXmax();

        TString func_name = TString::Format("custom_gaus_eta_%zu", i);
        TF1* custom_gaus = new TF1(func_name, "[0]*TMath::Exp(-0.5*TMath::Power((x-[1])/[2], 2))", fit_min, fit_max);
        custom_gaus->SetParameters(h1d->GetMaximum(), h1d->GetMean(), h1d->GetRMS());

        TFitResultPtr fit_result = h1d->Fit(custom_gaus, "QRS");

        if (fit_result == 0)
        {
            double chi2 = fit_result->Chi2();
            double ndf = fit_result->Ndf();
            double chi2_ndf = (ndf > 0) ? chi2 / ndf : 0;

            std::cout << "Eta Bin [" << eta_low << ", " << eta_high << "] | Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2_ndf << std::endl;

            double fit_mean = custom_gaus->GetParameter(1);
            double fit_mean_err = custom_gaus->GetParError(1);
            double fit_sigma = custom_gaus->GetParameter(2);
            double fit_sigma_err = custom_gaus->GetParError(2);

            int idx = gr_response->GetN();

            gr_response->SetPoint(idx, gen_eta_center, fit_mean);
            gr_response->SetPointError(idx, gen_eta_width / 2.0, fit_mean_err);

            if (fit_mean != 0)
            {
                double resolution = fit_sigma / fit_mean;
                double resolution_err = resolution * TMath::Sqrt(TMath::Power(fit_sigma_err / fit_sigma, 2) + TMath::Power(fit_mean_err / fit_mean, 2));
                gr_resolution->SetPoint(idx, gen_eta_center, resolution);
                gr_resolution->SetPointError(idx, gen_eta_width / 2.0, resolution_err);
            }

            gr_chi2->SetPoint(idx, gen_eta_center, chi2_ndf);
            gr_chi2->SetPointError(idx, gen_eta_width / 2.0, 0);
        }

        if (out_dir)
        {
            out_dir->cd();
            h1d->Write();
        }

        delete custom_gaus;
        delete h1d;
    }
    if (out_dir)
    {
        gr_resolution->Write();
        gr_response->Write();
        gr_chi2->Write();
    }

    return std::make_tuple(gr_response, gr_resolution, gr_chi2);
}

void JetEnergyScale::jetEnergyResponse()
{
    std::vector<TH2D*> etaProj;
    std::vector<TH2D*> ptProj;

    for (int i = 0; i < fMultCentBins.size() - 1; i++)
    {
        hEtaJES->GetZaxis()->SetRange(hEtaJES->GetZaxis()->FindBin(fMultCentBins[i]), hEtaJES->GetZaxis()->FindBin(fMultCentBins[i + 1] - 0.001));
        TH2D* hEtaProj = (TH2D*)hEtaJES->Project3D("xy");
        hEtaProj->SetName(Form("hEtaProj_%d_%d", (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));
        etaProj.push_back(hEtaProj);
        hPtJES->GetZaxis()->SetRange(hPtJES->GetZaxis()->FindBin(fMultCentBins[i]), hPtJES->GetZaxis()->FindBin(fMultCentBins[i + 1] - 0.001));
        TH2D* hPtProj = (TH2D*)hPtJES->Project3D("xy");
        hPtProj->SetName(Form("hPtProj_%d_%d", (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));
        ptProj.push_back(hPtProj);
    }

    for (int i = 0; i < etaProj.size(); ++i)
    {
        TFile* f1 = TFile::Open(Form("PtJESJERForCentMultBins%d_%d.root", (int)fMultCentBins[i], (int)fMultCentBins[i + 1]), "RECREATE");
        auto ptResScale = fitJetPtResponseCustomBins(ptProj[i], fPtBins, f1);
        f1->Write();
        f1->Close();
        TFile* f2 = TFile::Open(Form("EtaJESJERForCentMultBins%d_%d.root", (int)fMultCentBins[i], (int)fMultCentBins[i + 1]), "RECREATE");
        auto etaResScale = fitJetEtaResponseCustomBins(etaProj[i], fEtaBins, f2);
        f2->Write();
        f2->Close();
    }
}