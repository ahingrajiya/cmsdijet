#include "../interface/Unfolding.h"

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

TH1D* Unfolding::performUnfolding(RooUnfoldResponse* response, TH1D* measured, TH1D* hPurity, TH1D* hEfficiency, int iteration)
{
    TH1D* toUnfold = (TH1D*)measured->Clone("toUnfold");
    toUnfold->Multiply(hPurity);
    if (performValidation) iteration = 1;
    RooUnfoldBayes unfold(response, measured, iteration);
    TH1D* unfolded = (TH1D*)unfold.Hreco()->Clone("unfolded");
    unfolded->Multiply(hEfficiency);
    return unfolded;
}
