//Allie Reinsvold-Hall
//2016
//Root macro to fit trigger efficiency plots with an error function


{
  //Different fits to try 
    //  TF1 * error1 = new TF1("error1", "erf",0,20);
   //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[3]",20.,80.);
   // myFit1T1->SetParameters(0.5,10,0.5,0.5);
   //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf(x-[0])*[1]+[1]",25.,80.);
    //myFit1T1->SetParameters(60,0.5);
    //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf(x-[0])*[1]+[2]",25.,80.);
    //myFit1T1->SetParameters(30.,0.5,0.5);
    //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf(x-[0])*[1]+[2]",20.,80.);
     //myFit1T1->SetParameters(18.75,0.5,0.5);

  //Fits used for 2015 analysis
    //LeadLead fit
   // TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[2]",20.,80.);
    //myFit1T1->SetParameters(0.5,20,0.5);
    
    //TrailLead fit
    //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[2]",20.,80.);
   //myFit1T1->SetParameters(0.5,10,0.5);
    
    //TrailTrail fit
    //TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[2]",10.,80.);
    //myFit1T1->SetParameters(0.5,10,0.5);
    
    //LeadTrail fit:
   TF1 *myFit1T1 = new TF1("myFit1T1","TMath::Erf([0]*x-[1])*[2]+[2]",20.,80.);
    myFit1T1->SetParameters(0.5,50,0.5);
    
    //Input file
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
    
    TString extraText   = "";
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
    trigEff_Lead_Trail->Draw();
    trigEff_Lead_Trail->SetTitle("Sub-Leading Efficiency;Leading Photon P_{T} (GeV);Efficiency");
    //trigEff_Lead_Trail->GetXaxis()->SetTitleOffset(1.1);
    trigEff_Lead_Trail->Fit(myFit1T1);
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

    TLine *line = new TLine(18,1,120,1);
    line->SetLineColor(kBlack);
    line->SetLineStyle(9);
    line->Draw();
    
//    for(int it_lead = 0; it_lead < 41; it_lead++){
//        for(int it_trail =0; it_trail < 41; it_trail++){
//            float pass = h_2D_Pass->GetBinContent(it_trail, it_lead);
//            float all = h_2D_All->GetBinContent(it_trail,it_lead);
//            float eff = 0;
//            if(pass > 0 && all > 0) eff = pass/all;
//            else if (all > 0 && pass ==0) eff = 0.05;
//            h_2D_Efficiency->SetBinContent(it_trail, it_lead, eff);
//        }
//    }
//    
//    TCanvas* canv2 = new TCanvas("twoD","Total Trigger Efficiency",50,50,W_ref,H_ref);
//    canv2->cd();
//    canv2->SetFillColor(0);
//    canv2->SetBorderMode(0);
//    canv2->SetFrameFillStyle(0);
//    canv2->SetFrameBorderMode(0);
//    canv2->SetLeftMargin( L/W_ref );
//    canv2->SetRightMargin( R/W_ref );
//    canv2->SetTopMargin( T/H_ref );
//    canv2->SetBottomMargin( B/H_ref );
//    canv2->SetTickx(0);
//    canv2->SetTicky(0);
//    canv2->SetGrid();
//    gStyle->SetGridStyle(3);
//    //gStyle->SetOptFit(0);
//    //gStyle->SetOptStat(0);
//    
//    canv2->SetGridx();
//    canv2->SetGridy();
//    gPad->Update();
//    
//    canv2->cd();
//
//    latex.SetNDC();
//    latex.SetTextAngle(0);
//    latex.SetTextColor(kBlack);
//    latex.SetTextFont(cmsTextFont);
//    latex.SetTextSize(cmsTextSize*t);
//    latex.SetTextAlign(align_);
//    latex.DrawLatex(posX_, posY_, cmsText);
//    if( true )
//    {
//        latex.SetTextFont(extraTextFont);
//        latex.SetTextAlign(align_);
//        latex.SetTextSize(extraTextSize*t);
//        latex.DrawLatex(posX_ + relExtraDX*cmsTextSize*l, posY_, extraText);
//    }
//    latex.SetTextAlign(31);
//    latex.DrawLatex(1-r, posY_, lumiText);
//
//    h_2D_Efficiency->Draw("colz");
    
//    
//    canv1->Update();
//    canv1->RedrawAxis();
//    canv1->GetFrame()->Draw();
//    canv1->cd();


}
