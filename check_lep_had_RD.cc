double xy(double *x, double *par){

	double val = par[0]/x[0];
	return val;
}

void check_lep_had_RD(){

	TChain *t1 = new TChain("Sim");
	//t1->Add("/data2/users/xning/output/thre_track_leha_edep_nue_*GeV_1kevts.root");
	t1->Add("/data2/users/xning/output/thre_track_leha_edep_nue_1GeV_1kevts.root");
	double total_entries = t1->GetEntries();
	cout<<"total entries = "<<total_entries<<endl;
	//fill E_availList: 0 electron, 6 muon, 1 proton, 2 neutron, 3 pi+-, 4 pi0, 5 others.
	TH2D *h_axis = new TH2D("h_re_1","",1,0.3,1,1,0,1);
	h_axis->GetXaxis()->SetTitle("#bar{R}_{dep}");
	h_axis->GetYaxis()->SetTitle("#bar{#beta R_{C}} or #bar{R_{L}}");
	h_axis->GetXaxis()->CenterTitle();
	h_axis->GetYaxis()->CenterTitle();
	h_axis->GetXaxis()->SetTitleSize(0.05);
	h_axis->GetYaxis()->SetTitleSize(0.05);
	gStyle->SetOptStat(0);

	TH2D* h_Q_lep = new TH2D("h_Q_lep","",100,0,1,100,0,1);
	TH2D* h_Q_had = new TH2D("h_Q_had","",100,0,1,100,0,1);

	TH2D* h_L_lep = new TH2D("h_L_lep","",100,0,1,100,0,1);
	TH2D* h_L_had = new TH2D("h_L_had","",100,0,1,100,0,1);
	//h_L_lep->SetMarkerStyle(1);
	h_L_lep->SetMarkerColor(2);
	h_L_had->SetMarkerStyle(5);
	h_L_had->SetMarkerColor(2);
	h_L_had->SetMarkerSize(0.8);
	//
	//h_Q_lep->SetMarkerStyle(1);
	h_Q_lep->SetMarkerColor(4);
	h_Q_lep->SetLineWidth(0);
	h_Q_had->SetMarkerStyle(5);
	h_Q_had->SetMarkerColor(4);
	h_Q_had->SetMarkerSize(0.8);




	t1->Draw("(E_depoList_l[1]+E_depoList_l[2]+E_depoList_l[3]+E_depoList_l[5])/(E_depoList[1]+E_depoList[2]+E_depoList[3]+E_depoList[5]) : (E_depoList[1]+E_depoList[2]+E_depoList[3]+E_depoList[5])/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h_L_had","","");

	t1->Draw("0.83*(Q_depoList_thre[1]+Q_depoList_thre[2]+Q_depoList_thre[3]+Q_depoList_thre[5])/(E_depoList[1]+E_depoList[2]+E_depoList[3]+E_depoList[5]) : (E_depoList[1]+E_depoList[2]+E_depoList[3]+E_depoList[5])/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h_Q_had","","");

	t1->Draw("((E_depoList_l[0]+E_depoList_l[6]+E_depoList_l[4])/(E_depoList[0]+E_depoList[6]+E_depoList[4])): (E_depoList[0]+E_depoList[6]+E_depoList[4])/(E_availList[0]+E_availList[6]+E_availList[4])>>h_L_lep","","");

	t1->Draw("0.83*(Q_depoList_thre[0]+Q_depoList_thre[6]+Q_depoList_thre[4])/(E_depoList[0]+E_depoList[6]+E_depoList[4]) : (E_depoList[0]+E_depoList[6]+E_depoList[4])/(E_availList[0]+E_availList[6]+E_availList[4])>>h_Q_lep","","");


	auto f1 = new TF1("f1","xy",0.3,1,1);
	f1->SetParameter(0,0.35);
	f1->SetLineColor(1);
	auto f2 = new TF1("f2","xy",0.3,1,1);
	f2->SetParameter(0,0.5);
	f2->SetLineColor(1);

	auto f3 = new TF1("f3","xy",0.3,1,1);
	f3->SetParameter(0,0.42);
	f3->SetLineColor(1);
	f1->SetLineWidth(1);
	f2->SetLineWidth(1);
	f3->SetLineWidth(1);
	//	f3->SetLineStyle(7);
	//	f2->SetLineStyle(7);
	//	f1->SetLineStyle(7);
	TCanvas *c2; 
	c2 = new TCanvas("c2","c2",800,600);
	//	gPad->SetGrid();
	h_axis->Draw("Axis");
	h_L_had->Draw("same");
	h_Q_had->Draw("same");
	h_L_lep->Draw("same");
	h_Q_lep->Draw("same");
	f1->Draw("same");
	f2->Draw("same");
	f3->Draw("same");

	TLatex text;
	text.SetTextFont(133);
	text.SetTextSize(25);
	text.DrawLatex(0.36,0.78,"xy=0.35");
	text.DrawLatex(0.42,0.92,"xy=0.42");
	text.DrawLatex(0.56,0.93,"xy=0.5");


	TFile *file = new TFile("lep_had_RD_plot.root","recreate");
	h_Q_lep->Write("");
	h_Q_had->Write("");
	h_L_lep->Write("");
	h_L_had->Write("");

	file->Close();

	//TLegend *leg3 = new TLegend(0.55,0.72, 0.85,0.88);
	TLegend *leg3 = new TLegend(0.18,0.18, 0.85,0.24);
	//leg3->SetBorderSize(0);
	leg3->SetNColumns(4);
	auto entry = leg3->AddEntry(h_Q_lep, "Charge; e", "P");
	entry->SetTextSize(28);	
	entry = leg3->AddEntry(h_Q_had, "Charge; h", "P");
	entry->SetTextSize(28);	
	entry = leg3->AddEntry(h_L_lep, "Light; e", "P");
	entry->SetTextSize(28);	
	entry = leg3->AddEntry(h_L_had, "Light; h", "P");
	entry->SetTextSize(28);	
	leg3->Draw();


	c2->SaveAs("plot/Rf_Df.pdf");
	c2->SaveAs("plot/Rf_Df.C");

}
