void Draw_lep_had_LQ_sep(){
TCanvas *c1 = new TCanvas("c1","c1",800,600);
int ndiv = 505;

    TH2D *h_axis = new TH2D("h_re_1","",1,0,1.1,1,0,0.1);
    h_axis->Draw("");
	h_axis->GetYaxis()->SetNdivisions(ndiv);
    h_axis->GetXaxis()->SetTitle("Calorimeters response");
    h_axis->GetYaxis()->SetTitle("Probability");
	h_axis->GetXaxis()->CenterTitle();
	h_axis->GetYaxis()->CenterTitle();
//    h_axis->GetXaxis()->SetTitleOffset(0.9);
//    h_axis->GetXaxis()->SetTitleSize(0.1);
//    h_axis->GetXaxis()->SetLabelSize(0.08);
//    h_axis->GetYaxis()->SetLabelSize(0.08);
//    h_axis->GetXaxis()->SetTitleSize(0.06);
//    h_axis->GetYaxis()->SetTitleSize(0.06);
	
    gStyle->SetOptStat(0);


TChain *t1 = new TChain("Sim");
t1->Add("/data2/users/xning/output/thre_track_leha_edep_nue_*GeV_1kevts.root");
    TH1D* h_L_lep = new TH1D("h_L_lep","",100,0,1.1);
    TH1D* h_L_had_p = new TH1D("h_L_had_p","",100,0,1.1);
    TH1D* h_L_had_n = new TH1D("h_L_had_n","",100,0,1.1);
    TH1D* h_L_had_cp = new TH1D("h_L_had_cp","",100,0,1.1);

    h_L_lep->SetLineColor(4);
    h_L_had_p->SetLineColor(1);
    h_L_had_n->SetLineColor(2);
    h_L_had_cp->SetLineColor(4);
    h_axis->Draw("");

    t1->Draw("(E_depoList_l[1])/(E_availList[1])>>h_L_had_p","E_depoList_l[1]!=0","same hist");
    t1->Draw("(E_depoList_l[2])/(E_availList[2])>>h_L_had_n","E_depoList_l[2]!=0","same hist");
    t1->Draw("(E_depoList_l[3])/(E_availList[3])>>h_L_had_cp","E_depoList_l[3]!=0","same hist");
	h_L_had_p->Scale(1./h_L_had_p->Integral());
	h_L_had_n->Scale(1./h_L_had_n->Integral());
	h_L_had_cp->Scale(1./h_L_had_cp->Integral());


	TLegend *leg3 = new TLegend(0.7,0.60, 0.85,0.8);
    leg3->SetBorderSize(0);
    leg3->AddEntry(h_L_had_p, "p", "l");
    leg3->AddEntry(h_L_had_n, "n", "l");
    leg3->AddEntry(h_L_had_cp, "#pi^{#pm}", "l");
    leg3->Draw();




	c1->SaveAs("plot/lep_had_L_sep.pdf");
//
//TFile *f1 = new TFile("plot/lep_had_LQ.root","recreate");
//c1->Write();
//h_L_lep->Write();
//h_L_had->Write();
//h_Q_lep->Write();
//h_Q_had->Write();
//f1->Close();


}
