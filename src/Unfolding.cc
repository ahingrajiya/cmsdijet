#include "../interface/Unfolding.h"
Unfolding::Unfolding()
{
}

Unfolding::~Unfolding()
{
}

std::vector<TH1D*> Unfolding::unflattenHistogram(std::vector<double> ptBins, std::vector<double> xjBins, TH1D* flattenedHist, std::string name)
{
    std::vector<TH1D*> xjhistos;
    xjhistos.clear();
    int nptbins = ptBins.size() - 1;

    for (int i = 0; i < nptbins; ++i)
    {
        TH1D* xjhist = new TH1D(Form("%s_xj_histo_%i_%i", name.c_str(), (int)ptBins[i], (int)ptBins[i + 1]),
                                Form("Xj Histo for Pt %i to %i", (int)ptBins[i], (int)ptBins[i + 1]), xjBins.size() - 1, xjBins.data());

        xjhistos.push_back(xjhist);
    }

    for (int i = 1; i < flattenedHist->GetNbinsX() + 1; ++i)
    {
        float bincont = flattenedHist->GetBinContent(i);
        float binerr = flattenedHist->GetBinError(i);
        int histo_num = (i - 1) % nptbins;
        xjhistos[histo_num]->SetBinContent((int)(i / nptbins) + 1, bincont);

        xjhistos[histo_num]->SetBinError((int)(i / nptbins) + 1, binerr);
    }
    return xjhistos;
}

TH1D* Unfolding::unfold(RooUnfoldResponse* response, TH1D* measured, TH1D* purity, TH1D* efficiency, int iteration)
{
    TH1D* toUnfold = (TH1D*)measured->Clone("toUnfold");
    toUnfold->Multiply(purity);
    RooUnfoldBayes unfold(response, measured, iteration);
    TH1D* unfolded = (TH1D*)unfold.Hreco()->Clone("unfolded");
    unfolded->Multiply(efficiency);
    return unfolded;
}

void Unfolding::readHistograms(TFile* mcIn, TFile* dataIn, bool validation)
{
    if (validation)
    {
        hResponseMatrix3D[0] = (TH3D*)mcIn->Get("Unfolding/hResponseMatrixA_W");
        hResponseMatrix3D[1] = (TH3D*)mcIn->Get("Unfolding/hResponseMatrixB_W");

        hTotalReco2D[0] = (TH2D*)mcIn->Get("Unfolding/hTotalRecoA_W");
        hTotalReco2D[1] = (TH2D*)mcIn->Get("Unfolding/hTotalRecoB_W");

        hTotalTruth2D[0] = (TH2D*)mcIn->Get("Unfolding/hTotalTruthA_W");
        hTotalTruth2D[1] = (TH2D*)mcIn->Get("Unfolding/hTotalTruthB_W");
    }
    else
    {
        hResponseMatrix3D[0] = (TH3D*)mcIn->Get("Unfolding/hResponseMatrix_W");
        hTotalReco2D[0] = (TH2D*)mcIn->Get("Unfolding/hTotalReco_W");
        hTotalTruth2D[0] = (TH2D*)mcIn->Get("Unfolding/hTotalTruth_W");
        hDataReco2D = (TH2D*)dataIn->Get("Unfolding/hTotalRecoFlat_W");
    }
}

void Unfolding::projections(bool validation, float centMin, float centMax)
{
    if (validation)
    {
        for (int i = 0; i < 2; ++i)
        {
            hResponseMatrix3D[i]->GetZaxis()->SetRange(hResponseMatrix3D[i]->GetZaxis()->FindBin(centMin), hResponseMatrix3D[i]->GetZaxis()->FindBin(centMax - 0.001));
            hTotalReco2D[i]->GetYaxis()->SetRange(hTotalReco2D[i]->GetYaxis()->FindBin(centMin), hTotalReco2D[i]->GetYaxis()->FindBin(centMax - 0.001));
            hTotalTruth2D[i]->GetYaxis()->SetRange(hTotalTruth2D[i]->GetYaxis()->FindBin(centMin), hTotalTruth2D[i]->GetYaxis()->FindBin(centMax - 0.001));

            hResponseMatrix[i] = (TH2D*)hResponseMatrix3D[i]->Project3D("yx");
            hResponseMatrix[i]->SetName(Form("hResponseMatrix%i_%i_%i", i, (int)centMin, (int)centMax));

            hMatchedReco[i] = hResponseMatrix[i]->ProjectionX();
            hMatchedReco[i]->SetName(Form("hMatchedReco%i_%i_%i", i, (int)centMin, (int)centMax));

            hMatchedTruth[i] = hResponseMatrix[i]->ProjectionY();
            hMatchedTruth[i]->SetName(Form("hMatchedTruth%i_%i_%i", i, (int)centMin, (int)centMax));

            hTotalReco[i] = hTotalReco2D[i]->ProjectionX();
            hTotalReco[i]->SetName(Form("hTotalReco%i_%i_%i", i, (int)centMin, (int)centMax));

            hTotalTruth[i] = hTotalTruth2D[i]->ProjectionX();
            hTotalTruth[i]->SetName(Form("hTotalTruth%i_%i_%i", i, (int)centMin, (int)centMax));

            hPurity[i] = purity(hTotalReco[i], hMatchedReco[i]);
            hPurity[i]->SetName(Form("hPurity%i_%i_%i", i, (int)centMin, (int)centMax));

            hEfficiency[i] = efficiency(hTotalTruth[i], hMatchedTruth[i]);
            hEfficiency[i]->SetName(Form("hEfficiency%i_%i_%i", i, (int)centMin, (int)centMax));
        }
    }

    else
    {
        int i = 0;
        hResponseMatrix3D[i]->GetZaxis()->SetRange(hResponseMatrix3D[i]->GetZaxis()->FindBin(centMin), hResponseMatrix3D[i]->GetZaxis()->FindBin(centMax - 0.001));
        hTotalReco2D[i]->GetYaxis()->SetRange(hTotalReco2D[i]->GetYaxis()->FindBin(centMin), hTotalReco2D[i]->GetYaxis()->FindBin(centMax - 0.001));
        hTotalTruth2D[i]->GetYaxis()->SetRange(hTotalTruth2D[i]->GetYaxis()->FindBin(centMin), hTotalTruth2D[i]->GetYaxis()->FindBin(centMax - 0.001));
        hDataReco2D->GetYaxis()->SetRange(hDataReco2D->GetYaxis()->FindBin(centMin), hDataReco2D->GetYaxis()->FindBin(centMax - 0.001));

        hResponseMatrix[i] = (TH2D*)hResponseMatrix3D[i]->Project3D("yx");
        hResponseMatrix[i]->SetName(Form("hResponseMatrix%i_%i_%i", i, (int)centMin, (int)centMax));

        hMatchedReco[i] = hResponseMatrix[i]->ProjectionX();
        hMatchedReco[i]->SetName(Form("hMatchedReco%i_%i_%i", i, (int)centMin, (int)centMax));

        hMatchedTruth[i] = hResponseMatrix[i]->ProjectionY();
        hMatchedTruth[i]->SetName(Form("hMatchedTruth%i_%i_%i", i, (int)centMin, (int)centMax));

        hDataReco = hDataReco2D->ProjectionX();
        hDataReco->SetName(Form("hDataReco%i_%i_%i", i, (int)centMin, (int)centMax));

        hTotalReco[i] = hTotalReco2D[i]->ProjectionX();
        hTotalReco[i]->SetName(Form("hTotalReco%i_%i_%i", i, (int)centMin, (int)centMax));

        hTotalTruth[i] = hTotalTruth2D[i]->ProjectionX();
        hTotalTruth[i]->SetName(Form("hTotalTruth%i_%i_%i", i, (int)centMin, (int)centMax));

        hPurity[i] = purity(hTotalReco[i], hMatchedReco[i]);
        hPurity[i]->SetName(Form("hPurity%i_%i_%i", i, (int)centMin, (int)centMax));

        hEfficiency[i] = efficiency(hTotalTruth[i], hMatchedTruth[i]);
        hEfficiency[i]->SetName(Form("hEfficiency%i_%i_%i", i, (int)centMin, (int)centMax));
    }
}
TH1D* Unfolding::purity(TH1D* totalReco, TH1D* matchedReco)
{
    TH1D* hPurity_ = (TH1D*)matchedReco->Clone("hPurity_");
    hPurity_->Divide(totalReco);
    return hPurity_;
}

TH1D* Unfolding::efficiency(TH1D* totalTruth, TH1D* matchedtruth)
{
    TH1D* hEfficiency_ = (TH1D*)totalTruth->Clone("hEfficiency_");
    hEfficiency_->Divide(matchedtruth);
    return hEfficiency_;
}

void Unfolding::performUnfolding()
{
    TFile* out = TFile::Open(outputFile, "RECREATE");

    readHistograms(fMCIn, fDataIn, performValidation);

    std::vector<TH1D*> genXjHisto;
    std::vector<TH1D*> recoXjHisto;
    std::vector<TH1D*> unfoldedHisto;
    std::vector<TH1D*> unfoldValidationHisto;
    for (int i = 0; i < fMultCentBins.size() - 1; ++i)
    {
        projections(performValidation, fMultCentBins[i], fMultCentBins[i + 1]);

        if (performValidation)
        {
            for (int j = 0; j < 2; ++j)
            {
                RooUnfoldResponse response(hMatchedReco[j], hMatchedTruth[j], hResponseMatrix[j], "response", "Response Validation");
                TH1D* validation = unfold(&response, hTotalReco[j], hPurity[j], hPurity[j], 1);
                validation->SetName(Form("Validation%i_%i_%i", j, (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));

                std::stringstream validation_name;
                validation_name << "Validation_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1] << "_" << j;
                unfoldValidationHisto = unflattenHistogram(fPtBins, fXjBins, validation, validation_name.str());
                writeHisto(out, unfoldValidationHisto);
                unfoldValidationHisto.clear();

                validation_name.clear();
                validation_name << "Gen_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1] << "_" << j;
                genXjHisto = unflattenHistogram(fPtBins, fXjBins, hTotalTruth[j], validation_name.str());
                writeHisto(out, genXjHisto);
                genXjHisto.clear();

                validation_name.clear();
                validation_name << "Reco_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1] << "_" << j;
                recoXjHisto = unflattenHistogram(fPtBins, fXjBins, hTotalReco[j], validation_name.str());
                writeHisto(out, recoXjHisto);
                recoXjHisto.clear();
            }

            RooUnfoldResponse response0(hMatchedReco[0], hMatchedTruth[0], hResponseMatrix[0], "response0", "Response Validation");
            TH1D* unfolded1 = unfold(&response0, hTotalReco[1], hPurity[0], hPurity[0], iterations);
            unfolded1->SetName(Form("Unfolded%i_%i_%i", 1, (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));
            std::stringstream unfold_name;
            unfold_name << "Unfolded_" << 1 << "_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1];
            unfoldedHisto = unflattenHistogram(fPtBins, fXjBins, unfolded1, unfold_name.str());
            writeHisto(out, unfoldedHisto);
            unfoldedHisto.clear();

            RooUnfoldResponse response1(hMatchedReco[1], hMatchedTruth[1], hResponseMatrix[1], "response0", "Response Validation");
            TH1D* unfolded0 = unfold(&response1, hTotalReco[0], hPurity[1], hPurity[1], iterations);
            unfolded0->SetName(Form("Unfolded%i_%i_%i", 0, (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));
            unfold_name.clear();
            unfold_name << "Unfolded_" << 0 << "_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1];
            unfoldedHisto = unflattenHistogram(fPtBins, fXjBins, unfolded0, unfold_name.str());
            writeHisto(out, unfoldedHisto);
            unfoldedHisto.clear();
        }
        else
        {
            RooUnfoldResponse response(hMatchedReco[0], hMatchedTruth[0], hResponseMatrix[0], "response", "Response Validation");
            TH1D* dataUnfold = unfold(&response, hDataReco, hPurity[0], hPurity[0], iterations);
            dataUnfold->SetName(Form("dataUnfold_%i_%i", (int)fMultCentBins[i], (int)fMultCentBins[i + 1]));

            std::stringstream dataUnfold_name;
            dataUnfold_name << "dataUnfold_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1];
            unfoldedHisto = unflattenHistogram(fPtBins, fXjBins, dataUnfold, dataUnfold_name.str());
            writeHisto(out, unfoldedHisto);
            unfoldedHisto.clear();

            std::stringstream gen_name;
            gen_name << "Gen_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1];
            genXjHisto = unflattenHistogram(fPtBins, fXjBins, hTotalTruth[0], gen_name.str());
            writeHisto(out, genXjHisto);
            genXjHisto.clear();

            std::stringstream reco_name;
            reco_name << "Reco_" << fMultCentBins[i] << "_" << fMultCentBins[i + 1];
            recoXjHisto = unflattenHistogram(fPtBins, fXjBins, hTotalReco[0], reco_name.str());
            writeHisto(out, recoXjHisto);
            recoXjHisto.clear();
        }
    }
    out->Write();
    out->Close();
}

void Unfolding::writeHisto(TFile* out, std::vector<TH1D*> histo)
{
    out->cd();
    for (int i = 0; i < histo.size(); ++i)
    {
        histo[i]->Write();
    }
}
