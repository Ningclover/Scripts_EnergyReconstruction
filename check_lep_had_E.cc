
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
double GetMaxX(TH1D *h1){
    int Bin = h1->GetMaximumBin();
    double x = h1->GetXaxis()->GetBinCenter(Bin); 
    return x;
}

double GetMaxX_Fit(TH1D *h1){
	h1->Smooth();
    int Bin = h1->GetMaximumBin();
    double x1 = h1->GetXaxis()->GetBinCenter(Bin-5); 
    double x2= h1->GetXaxis()->GetBinCenter(Bin+5); 
	TF1 *f1 = new TF1("f1","gaus",x1,x2);
	h1->Fit("f1","R","",x1,x2);
	double par[3];
 	 f1->GetParameters(par);
	cout<<par[1]<<endl;
	f1->Draw("same");
    return par[1];
}

void Ratio_on_E(double E, double *ratio){
	TChain *t1 = new TChain("Sim");
	t1->Add(Form("/data2/users/xning/output/thre_track_leha_E_%.1f.root",E));
	gStyle->SetOptStat(0);
	TH1D* h_L_lep = new TH1D("h_L_lep","",100,0,1);
	TH1D* h_L_had = new TH1D("h_L_had","",100,0,1);

	TH1D* h_Q_lep = new TH1D("h_Q_lep","",100,0,1);
	TH1D* h_Q_had = new TH1D("h_Q_had","",100,0,1);
	h_Q_lep->SetLineColor(kBlue);
	h_Q_had->SetLineColor(kGreen);
	t1->Draw("(E_depoList_l[0]+E_depoList_l[6]+E_depoList_l[4])/(E_availList[0]+E_availList[6]+E_availList[4])>>h_L_lep","","same");
	t1->Draw("(E_depoList_l[1]+E_depoList_l[2]+E_depoList_l[3]+E_depoList_l[5])/(E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])>>h_L_had","","same");
	h_L_lep->Draw();
	h_L_had->Draw("same");
	double RE_light = GetMaxX(h_L_lep);
	double RH_light = GetMaxX_Fit(h_L_had);
	double E_over_H_light =RE_light/RH_light; 
	//c1->SaveAs("tmp.pdf");

    t1->Draw("(Q_depoList_thre[0]+Q_depoList_thre[6]+Q_depoList_thre[4])/(E_availList[0]+E_availList[6]+E_availList[4])*0.83>>h_Q_lep","","same");
    t1->Draw("(Q_depoList_thre[1]+Q_depoList_thre[2]+Q_depoList_thre[3]+Q_depoList_thre[5])/            (E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])*0.83>>h_Q_had","","same");
	h_Q_lep->Draw();
	h_Q_had->Draw("same");
	double RE_charge = GetMaxX(h_Q_lep);
	//double RH_charge = GetMaxX(h_Q_had);
	double RH_charge = GetMaxX_Fit(h_Q_had);
	double E_over_H_charge =RE_charge/RH_charge; 
	//c1->SaveAs("tmp.pdf");

	cout<<E<<"  "<<E_over_H_light<<" vs "<<E_over_H_charge<<endl;
	ratio[0] = E_over_H_light;
	ratio[1] = E_over_H_charge;
	delete h_L_lep;
	delete h_L_had;
	delete h_Q_lep;
	delete h_Q_had;

}

void check_lep_had_E(){
	//gPad->SetGrid();
//	c1->SaveAs("tmp.pdf[");
	double Efield[] = {0.1,0.3,0.5,0.7,1,1.5,2.5};
	const int N = sizeof(Efield)/sizeof(Efield[0]);
	double E_O_H_light[N];	
	double E_O_H_charge[N];	
	for(int i=0;i<N;i++){
		double ratio[2];
		Ratio_on_E(Efield[i],ratio);
		E_O_H_light[i] = ratio[0];
		E_O_H_charge[i] = ratio[1];
	}
		
//	c1->SaveAs("tmp.pdf]");


	TGraph *g_light = new TGraph(N,Efield,E_O_H_light);
	TGraph *g_charge = new TGraph(N,Efield,E_O_H_charge);

	g_light->Draw("Al ");
	g_light->SetLineColor(2);
	g_light->SetLineWidth(2);
	g_light->GetYaxis()->SetRangeUser(0.8,1.4);
	g_light->GetXaxis()->SetRangeUser(0,2);
	g_light->GetXaxis()->SetTitle("Drift E field [kV/cm]");
	g_light->GetYaxis()->SetTitle("e/h");
	g_light->GetXaxis()->CenterTitle();
	g_light->GetYaxis()->CenterTitle();
	//g_charge->Draw("same l *");

	c1->SaveAs("plot/E_H_Efield.pdf");
	c1->SaveAs("plot/E_H_Efield.C");

	TFile *f1 = new TFile("plot/E_H_Efield.root","recreate");
	g_light->Write();
	g_charge->Write();
	c1->Write();
	f1->Close();
	

	}
