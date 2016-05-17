int
WriteLimitCommands() {
    int m_gluino[] = {1000, 1100, 1200, 1300, 1350, 1400, 1450, 1500, 1550,
                      1600, 1650, 1700, 1750, 1800};
    int m_neutralino[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
                          1100, 1200, 1300, 1400, 1500, 1600, 1700};
    
    TFile* f_in = new TFile("SignalExpectation_NewNtuples.root");
    TH2D* h_in1 = f_in->Get("h_MET100to110_Grid");
    TH2D* h_in2 = f_in->Get("h_MET110to120_Grid");
    TH2D* h_in3 = f_in->Get("h_MET120to140_Grid");
    TH2D* h_in4 = f_in->Get("h_MET140to6000_Grid");
    TH2D* h_inStat1 = f_in->Get("h_MET100to110_GridStatError");
    TH2D* h_inStat2 = f_in->Get("h_MET110to120_GridStatError");
    TH2D* h_inStat3 = f_in->Get("h_MET120to140_GridStatError");
    TH2D* h_inStat4 = f_in->Get("h_MET140to6000_GridStatError");
    TH2D* h_inUp1 = f_in->Get("h_MET100to110_GridJESUpError");
    TH2D* h_inUp2 = f_in->Get("h_MET110to120_GridJESUpError");
    TH2D* h_inUp3 = f_in->Get("h_MET120to140_GridJESUpError");
    TH2D* h_inUp4 = f_in->Get("h_MET140to6000_GridJESUpError");
    TH2D* h_inDown1 = f_in->Get("h_MET100to110_GridJESDownError");
    TH2D* h_inDown2 = f_in->Get("h_MET110to120_GridJESDownError");
    TH2D* h_inDown3 = f_in->Get("h_MET120to140_GridJESDownError");
    TH2D* h_inDown4 = f_in->Get("h_MET140to6000_GridJESDownError");
    
    // Scale by trigger efficiency * scale factor
    double scale_factor = 0.993 * 0.986 * 0.983 * 0.983;
    h_in1->Scale(scale_factor);
    h_in2->Scale(scale_factor);
    h_in3->Scale(scale_factor);
    h_in4->Scale(scale_factor);
    
    ofstream f_out;
    f_out.open("limitCommands.sh");
    f_out << "#!/bin/sh" << std::endl << std::endl;
    
    for (int i = 1; i <= 14; i++) {
        for (int j = 1; j <= 17; j++) {
            if (h_in4->GetBinContent(i, j) != 0.0) {
                double uncertUp1 = TMath::Abs(h_inUp1->GetBinContent(i, j));
                double uncertUp2 = TMath::Abs(h_inUp2->GetBinContent(i, j));
                double uncertUp3 = TMath::Abs(h_inUp3->GetBinContent(i, j));
                double uncertUp4 = TMath::Abs(h_inUp4->GetBinContent(i, j));
                double uncertDown1 = TMath::Abs(h_inDown1->GetBinContent(i, j));
                double uncertDown2 = TMath::Abs(h_inDown2->GetBinContent(i, j));
                double uncertDown3 = TMath::Abs(h_inDown3->GetBinContent(i, j));
                double uncertDown4 = TMath::Abs(h_inDown4->GetBinContent(i, j));
                
                f_out << "cp counting_t5gg_XXX_YYY.txt counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/T5GG1/" << setprecision(3) << h_in1->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/T5GG2/" << setprecision(3) << h_in2->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/T5GG3/" << setprecision(3) << h_in3->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/T5GG4/" << setprecision(3) << h_in4->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/MCS1/" << setprecision(4) << 1.0 + h_inStat1->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/MCS2/" << setprecision(4) << 1.0 + h_inStat2->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/MCS3/" << setprecision(4) << 1.0 + h_inStat3->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/MCS4/" << setprecision(4) << 1.0 + h_inStat4->GetBinContent(i, j) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/JES1/" << setprecision(4) << 1.0 + TMath::Max(uncertUp1, uncertDown1) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/JES2/" << setprecision(4) << 1.0 + TMath::Max(uncertUp2, uncertDown2) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/JES3/" << setprecision(4) << 1.0 + TMath::Max(uncertUp3, uncertDown3) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
                f_out << "sed -i.tmp 's/JES4/" << setprecision(4) << 1.0 + TMath::Max(uncertUp4, uncertDown4) << "/g' counting_t5gg_" << m_gluino[i - 1] << "_" << m_neutralino[j - 1] << ".txt" << std::endl;
            }
        }
    }
    
    return 1;
}
