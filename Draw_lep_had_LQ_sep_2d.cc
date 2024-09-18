void Draw_lep_had_LQ_sep_2d(){
TCanvas *c1 = new TCanvas("c1","c1",800,600);

int ndiv = 505;

    TH2D *h_axis = new TH2D("h_re_1","",1,0,1.2,1,0,1);

	h_axis->GetYaxis()->SetNdivisions(ndiv);
    h_axis->GetXaxis()->SetTitle("Calorimeter response");
    h_axis->GetYaxis()->SetTitle("E_{component}/E_{avail;had}");
	h_axis->GetXaxis()->CenterTitle();
	h_axis->GetYaxis()->CenterTitle();

    TH2D *h_axis_2 = new TH2D("h_re_2","",1,0,1,1,0,3000);

	h_axis_2->GetYaxis()->SetNdivisions(ndiv);
    h_axis_2->GetXaxis()->SetTitle("Calorimeter response");
    h_axis_2->GetYaxis()->SetTitle("E_{component}");
	h_axis_2->GetXaxis()->CenterTitle();
	h_axis_2->GetYaxis()->CenterTitle();
//    h_axis->GetXaxis()->SetTitleOffset(0.9);
//    h_axis->GetXaxis()->SetTitleSize(0.1);
//    h_axis->GetXaxis()->SetLabelSize(0.08);
//    h_axis->GetYaxis()->SetLabelSize(0.08);
//    h_axis->GetXaxis()->SetTitleSize(0.06);
//    h_axis->GetYaxis()->SetTitleSize(0.06);
	
//    gStyle->SetOptStat(0);


TChain *t1 = new TChain("Sim");
t1->Add("/data2/users/xning/output/thre_track_leha_edep_nue_*GeV_1kevts.root");
    TH2D* h_L_had_p_E = new TH2D("h_L_had_p_E","",100,0,1,100,0,3000);
    TH2D* h_L_had_n_E = new TH2D("h_L_had_n_E","",100,0,1,100,0,3000);
    TH2D* h_L_had_cp_E = new TH2D("h_L_had_cp_E","",100,0,1,100,0,3000);
    TH2D* h_L_had_p = new TH2D("h_L_had_p","",100,0,1,100,0,1);
    TH2D* h_L_had_n = new TH2D("h_L_had_n","",100,0,1,100,0,1);
    TH2D* h_L_had_cp = new TH2D("h_L_had_cp","",100,0,1,100,0,1);

	h_L_had_p->SetMarkerColor(1);
	h_L_had_n->SetMarkerColor(2);
	h_L_had_cp->SetMarkerColor(4);
	h_L_had_p_E->SetMarkerColor(1);
	h_L_had_n_E->SetMarkerColor(2);
	h_L_had_cp_E->SetMarkerColor(4);
//	h_L_had_p->SetMarkerStyle(5);
//	h_L_had_n->SetMarkerStyle(5);
//	h_L_had_cp->SetMarkerStyle(5);

//    h_Q_lep->SetLineColor(4);
//    h_Q_had_p->SetLineColor(2);
//    h_Q_had_n->SetLineColor(3);
//    h_Q_had_cp->SetLineColor(1);
//    h_L_lep->SetLineColor(4);
//    h_L_had_p->SetLineColor(2);
//    h_L_had_n->SetLineColor(3);
//    h_L_had_cp->SetLineColor(1);

TH1D *h1 = new TH1D("h1","h1",100,0,1);
TH1D *h2 = new TH1D("h2","h1",100,0,1);
TH1D *h3 = new TH1D("h3","h1",100,0,1);


    t1->Draw("E_availList[1]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h1","E_availList[1]!=0","");
    t1->Draw("E_availList[2]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h2","E_availList[2]!=0","same");
    t1->Draw("E_availList[3]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h3","E_availList[3]!=0","same");
	h1->GetYaxis()->SetRangeUser(0,150);
	h1->GetXaxis()->SetTitle("E_{component}/E_{avail;had}");
	h1->SetLineColor(1);
	h2->SetLineColor(2);
	h3->SetLineColor(4);
	TLegend *leg3 = new TLegend(0.6,0.70, 0.85,0.85);
    leg3->SetBorderSize(0);
    leg3->AddEntry(h1, "p", "l");
    leg3->AddEntry(h2, "n", "l");
    leg3->AddEntry(h3, "#pi^{#pm}", "l");
    leg3->Draw();
c1->SaveAs("plot/had_avail_sep_1d.pdf");



    t1->Draw("E_availList[1]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5]):(E_depoList_l[1])/(E_availList[1])>>h_L_had_p","E_depoList_l[1]!=0","");
    t1->Draw("E_availList[2]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[4]+E_availList[5]):(E_depoList_l[2])/(E_availList[2])>>h_L_had_n","E_depoList_l[2]!=0","");
    t1->Draw("E_availList[3]/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5]):(E_depoList_l[3])/(E_availList[3])>>h_L_had_cp","E_depoList_l[3]!=0","");
    t1->Draw("E_availList[1]:(E_depoList_l[1])/(E_availList[1])>>h_L_had_p_E","E_depoList_l[1]!=0","");
    t1->Draw("E_availList[2]:(E_depoList_l[2])/(E_availList[2])>>h_L_had_n_E","E_depoList_l[2]!=0","");
    t1->Draw("E_availList[3]:(E_depoList_l[3])/(E_availList[3])>>h_L_had_cp_E","E_depoList_l[3]!=0","");
//	h_L_lep->Scale(1./h_L_lep->Integral());
//	h_L_had_p->Scale(1./h_L_had_p->Integral());
//	h_L_had_n->Scale(1./h_L_had_n->Integral());
//	h_L_had_cp->Scale(1./h_L_had_cp->Integral());
//	text.DrawLatex(0.1,0.8,"(Light)");

    h_axis->Draw("");
	h_L_had_p->Draw("same");
	h_L_had_n->Draw("same");
	h_L_had_cp->Draw("same");

//	cout<<h_L_had_n->Integral()<<endl;

	TLegend *leg4 = new TLegend(0.75,0.70, 0.85,0.85);
    //leg4->SetBorderSize(0);
    leg4->AddEntry(h_L_had_p, "p", "p");
    leg4->AddEntry(h_L_had_n, "n", "p");
    leg4->AddEntry(h_L_had_cp, "#pi^{#pm}", "p");
    leg4->Draw();



	c1->SaveAs("plot/had_sep_2d_ratio.pdf");

    h_axis_2->Draw("");
    h_L_had_p_E->Draw("same");
    h_L_had_n_E->Draw("same");
    h_L_had_cp_E->Draw("same");
    leg4->Draw();
	c1->SaveAs("plot/had_sep_2d_E.pdf");



//
//TFile *f1 = new TFile("plot/lep_had_LQ.root","recreate");
//c1->Write();
//h_L_lep->Write();
//h_L_had->Write();
//h_Q_lep->Write();
//h_Q_had->Write();
//f1->Close();


}
