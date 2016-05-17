TGraph*
MakeLimitGraph(TH2F* h) {
    TGraph* g = new TGraph();
    Int_t n = 0, m = 19;
    
    for (size_t i = 1; i <= m; i++) {
        Float_t x = 0.0;
        Float_t y = h->GetYaxis()->GetBinCenter(i);
        
        for (size_t j = 1; j < h->GetNbinsX(); j++) {
            Float_t xLow = h->GetXaxis()->GetBinCenter(j);
            Float_t xHigh = h->GetXaxis()->GetBinCenter(1 + j);
            Float_t zLow = h->GetBinContent(j, i);
            Float_t zHigh = h->GetBinContent(1 + j, i);
            
            if (zLow < 1.0 && zHigh > 1.0) {
                x = xLow + (xHigh - xLow) * (1.0 - zLow) / (zHigh - zLow);
                
                g->SetPoint(n, x, y);
                n++;
                break;
            }
        }
    }
    return g;
}


TH2F*
ScaleLimit(TH2F* h, TString s, Bool_t scaleByXSec, Float_t sigma) {
    TH2F* h_new = (TH2F*)h->Clone(s);
    
    for (size_t i = 1; i <= h_new->GetNbinsX(); i++) {
        for (size_t j = 1; j <= h_new->GetNbinsY(); j++) {
            ifstream f_xSec("SusyCrossSections13TevSquarkSquark.txt");
            Float_t mSusy, xSec, unc;
            Float_t m = h_new->GetXaxis()->GetBinCenter(i);
            Float_t r = h_new->GetBinContent(i, j);
            Bool_t foundM = kFALSE;
            
            // Kludge to account for binning change:
	    if (m == 1487.5)
	      m = 1500.0;
            
            while (f_xSec >> mSusy >> xSec >> unc) {
                if (mSusy == m) {
                    if (scaleByXSec)
                        r *= xSec;
                    
                    r /= 1.0 + sigma * unc / 100.0;
                    foundM = kTRUE;
                    break;
                }
            }
            
            if (!foundM)
                r = -1.0;
            
            h_new->SetBinContent(i, j, r);
        }
    }
    
    return h_new;
}


void
DrawLimitCanvas(TString s_expectedLimit="ExpLimMid.root",
                TString s_expectedLimitLow="ExpLimDown.root",
                TString s_expectedLimitHigh="ExpLimUp.root",
                TString s_observedLimit="ObsLim.root") {
    TFile* f_expectedLimit = new TFile(s_expectedLimit);
    TFile* f_expectedLimitLow = new TFile(s_expectedLimitLow);
    TFile* f_expectedLimitHigh = new TFile(s_expectedLimitHigh);
    TFile* f_observedLimit = new TFile(s_observedLimit);
    
    TH2F* h_expectedLimit = (TH2F*)f_expectedLimit->Get("h");
    TH2F* h_expectedLimitLow = (TH2F*)f_expectedLimitLow->Get("h");
    TH2F* h_expectedLimitHigh = (TH2F*)f_expectedLimitHigh->Get("h");
    TH2F* h_observedLimit = (TH2F*)f_observedLimit->Get("h");

    TH2F* h_xSecLimit = ScaleLimit(h_observedLimit, "h", kTRUE, 0.0);
    TH2F* h_observedLimitLow = ScaleLimit(h_observedLimit, "h", kFALSE, -1.0);
    TH2F* h_observedLimitHigh = ScaleLimit(h_observedLimit, "h", kFALSE, 1.0);
    
    TGraph* g_expectedLimit = MakeLimitGraph(h_expectedLimit);
    TGraph* g_expectedLimitLow = MakeLimitGraph(h_expectedLimitLow);
    TGraph* g_expectedLimitHigh = MakeLimitGraph(h_expectedLimitHigh);
    TGraph* g_observedLimit = MakeLimitGraph(h_observedLimit);
    TGraph* g_observedLimitLow = MakeLimitGraph(h_observedLimitLow);
    TGraph* g_observedLimitHigh = MakeLimitGraph(h_observedLimitHigh);
    
    gStyle->SetPadRightMargin(0.16);
    TFile* f_limitCanvas = new TFile("LimitCanvas.root", "recreate");
    TCanvas* c_limit = new TCanvas("c_limit", "", 580, 620);
    c_limit->SetLogz();
    
    Int_t limitPalette[255];
    Double_t red[] = {0.5, 0.5, 1.0, 1.0, 1.0};
    Double_t green[] = {0.5, 1.0, 1.0, 0.6, 0.5};
    Double_t blue[] = {1.0, 1.0, 0.5, 0.4, 0.5};
    Double_t length[] = {0.0, 0.34, 0.61, 0.84, 1.0};
    Int_t table = TColor::CreateGradientColorTable(5, length, red, green, blue,
    255);
    
    for (size_t i = 0; i < 255; i++)
        limitPalette[i] = table + i;
    
    h_xSecLimit->GetXaxis()->SetTitle("M_{#tilde{g}} (GeV)");
    h_xSecLimit->GetYaxis()->SetTitle("M_{#tilde{#chi}_{1}^{0}} (GeV)  ");
    h_xSecLimit->GetZaxis()->SetLabelOffset(-0.003);
    h_xSecLimit->GetZaxis()->SetLabelSize(0.03);
    h_xSecLimit->GetZaxis()->SetTitleOffset(0.9);
    h_xSecLimit->GetZaxis()->SetLabelSize(0.04);
    h_xSecLimit->GetZaxis()->SetTitle("95% CL limit on #sigma (pb)    ");
    h_xSecLimit->SetContour(255);
    h_xSecLimit->GetZaxis()->SetRangeUser(0.004, 0.007);
    h_xSecLimit->SetTitle("");
    h_xSecLimit->Draw("colz");
    
    g_expectedLimit->SetLineColor(kRed+1);
    g_expectedLimit->SetLineWidth(2);
    g_expectedLimit->Draw("C same");
    
    g_expectedLimitLow->SetLineColor(kRed+1);
    g_expectedLimitLow->SetLineStyle(2);
    g_expectedLimitLow->SetLineWidth(2);
    g_expectedLimitLow->Draw("C same");
    
    g_expectedLimitHigh->SetLineColor(kRed+1);
    g_expectedLimitHigh->SetLineStyle(2);
    g_expectedLimitHigh->SetLineWidth(2);
    g_expectedLimitHigh->Draw("C same");
    
    g_observedLimit->SetLineWidth(2);
    g_observedLimit->Draw("C same");
    
    g_observedLimitLow->SetLineStyle(2);
    g_observedLimitLow->SetLineWidth(2);
    g_observedLimitLow->Draw("C same");
    
    g_observedLimitHigh->SetLineStyle(2);
    g_observedLimitHigh->SetLineWidth(2);
    g_observedLimitHigh->Draw("C same");
    
    TLegend* le_limit = new TLegend(0.19, 0.72, 0.48, 0.84);
    le_limit->SetFillStyle(0);
    le_limit->SetLineColor(kWhite);
    le_limit->SetTextSize(0.0325);
    le_limit->SetTextFont(42);
    le_limit->AddEntry(g_observedLimit, "Obs. limit", "l");
    le_limit->AddEntry(g_observedLimitLow, "Obs. limit #pm 1 #sigma_{th}",
                       "l");
    le_limit->AddEntry(g_expectedLimit, "Exp. limit", "l");
    le_limit->AddEntry(g_expectedLimitLow, "Exp. limit #pm 1 #sigma_{ex}",
                       "l");
    le_limit->Draw("same");
    
    TLatex* la_limit = new TLatex();
    la_limit->SetNDC();
    
    la_limit->SetTextAlign(13);
    la_limit->SetTextSize(0.044);
    la_limit->SetTextFont(42);
    la_limit->DrawLatex(0.6, 0.998, "2.3 fb^{-1} (13 TeV)");
    
    la_limit->SetTextAlign(11);
    la_limit->SetTextSize(0.044);
    la_limit->SetTextFont(62);
    la_limit->DrawLatex(0.2, 0.96, "CMS");
    
    la_limit->SetTextAlign(11);
    la_limit->SetTextSize(0.044);
    la_limit->SetTextFont(42);
    la_limit->DrawLatex(0.3, 0.96, "Preliminary");
    
    la_limit->SetTextSize(0.04);
    la_limit->SetTextFont(42);
    la_limit->DrawLatex(
        0.2, 0.9,
        "pp #rightarrow #tilde{g}#tilde{g}, #tilde{g} #rightarrow qq#tilde{#chi}_{1}^{0}, #tilde{#chi}_{1}^{0} #rightarrow #gamma#tilde{G}"
    );
    
    la_limit->DrawLatex(0.2, 0.85, "NLO + NLL exclusion");
    
    c_limit->Write();
    f_limitCanvas->Close();
}
