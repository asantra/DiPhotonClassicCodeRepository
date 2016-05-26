//Allie Reinsvold-Hall      
//2016 
//Root macro to fit trigger efficiency versus Invariant Mass with an error function  
{
    //  TF1 * error1 = new TF1("error1", "erf",0,20);
   TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[3]",85.,120.);
    myFit1T1->SetParameters(0.4,38.0,0.5,0.5);
    
    //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])+[2]",85.,120.);
    //myFit1T1->SetParameters(0.4,38.0,0.5);
    
    TFile *f0 = TFile::Open("hist_TnPv2_analysis.root","UPDATE");
    f0->cd();
    
    
    int H_ref = 850;
    int W_ref = 900;
    
    // references for T, B, L, R
    float T = 0.08*H_ref;
    float B = 0.12*H_ref;
    float L = 0.12*W_ref;
    float R = 0.04*W_ref;
    
    int   align_       = 10*1+1;
    float relPosX      = 0.045;
    float relPosY      = -0.01;
    float relExtraDX   = 1.5;
    
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold
    float cmsTextSize   = 0.5;
    
    TString extraText   = ""; //Like Preliminary
    float extraTextFont = 52;  // default is helvetica-italics
    float extraOverCmsTextSize  = 0.7;
    float extraTextSize = extraOverCmsTextSize*cmsTextSize;
    
    TCanvas* canv1 = new TCanvas("efficiency","Trigger Efficiency",50,50,W_ref,H_ref);
    canv1->cd();
    canv1->SetFillColor(0);
    canv1->SetBorderMode(0);
    canv1->SetFrameFillStyle(0);
    canv1->SetFrameBorderMode(0);
    canv1->SetLeftMargin( L/W_ref );
    canv1->SetRightMargin( R/W_ref );
    canv1->SetTopMargin( T/H_ref );
    canv1->SetBottomMargin( B/H_ref );
    canv1->SetTickx(0);
    canv1->SetTicky(0);
    canv1->SetGrid();
    gStyle->SetGridStyle(3);
    //gStyle->SetOptFit(0);
    //gStyle->SetOptStat(0);
    
    canv1->SetGridx();
    canv1->SetGridy();
    gPad->Update();
    
    //trigEff_Lead_Trail->SetStats(kFALSE);
    trigEff_TotalInvMass->Draw();
    trigEff_TotalInvMass->SetTitle("Total Trigger Efficiency;Diphoton Invariant Mass P_{T} (GeV);Efficiency");
    //trigEff_TotalInvMass->GetXaxis()->SetRangeUser(80,120);
    trigEff_TotalInvMass->Fit(myFit1T1);
    gStyle->SetOptFit(0);
    gPad->Update();
    
    TString lumiText = "2.26 fb^{-1}";
    float r = canv1->GetRightMargin();
    float l = canv1->GetLeftMargin();
    float posX_ =   l + relPosX*(1-l-r);
    
    
    float t = canv1->GetTopMargin();
    float b = canv1->GetBottomMargin();
    float posY_ = 1-t - relPosY*(1-t-b);
    
    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    latex.SetTextFont(cmsTextFont);
    latex.SetTextSize(cmsTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, cmsText);
    if( true )
    {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize*t);
        latex.DrawLatex(posX_ + relExtraDX*cmsTextSize*l, posY_, extraText);
    }
    latex.SetTextAlign(31);
    latex.DrawLatex(1-r, posY_, lumiText);

    TLine *line = new TLine(80,1,120,1);
    line->SetLineColor(kBlack);
    line->SetLineStyle(9);
    line->Draw();

}
