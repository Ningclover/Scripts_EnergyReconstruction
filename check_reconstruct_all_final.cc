double GetMostProb(TH1D *h1){
	int Bin = h1->GetMaximumBin();
	double x = h1->GetXaxis()->GetBinCenter(Bin); 
	return x;
}

void check_reconstruct_all_final(){
	gStyle->SetOptStat(0);
	double energy = 1;
	TString lep = "e";
	//	TFile *f1 = new TFile("/home/xning/output/output_thres.root","read");
	TChain *t1 = new TChain("Sim");
	int color2[]={1,2,kGreen+2,4,2,6,5};
	int color[]={1,kGreen+2,4,2,6,5};
	//t1->Add("/data2/users/xning/output/thre_track_leha_edep_nu"+lep+Form("_%.0fGeV_1kevts.root",energy));
	t1->Add(TString("/data2/users/xning/output/thre_track_leha_E_edep")+Form("_%.1f_10000_12.root",energy));
	//t1->Add("/data2/users/xning/output/thre_track_leha_edep_nu"+lep+"_*_1kevts.root");
	double E_input = energy*1000;
	cout<<t1->GetEntries()<<endl;
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	gPad->SetGrid();
	TH1D *h1 = new TH1D("h1","",200,0,6000);
	TH1D *h2 = new TH1D("h2","",200,0,6000);
	TH1D *h3 = new TH1D("h3","",200,0,6000);
	TH1D *h4 = new TH1D("h4","",200,0,6000);
	TH1D *h5 = new TH1D("h5","",200,0,6000);
	t1->Draw("E_avail>>h1");
	t1->Draw("E_depoTotal>>h2","","same");
	t1->Draw("Q_depoTotal*0.83>>h3","","same");
	//t1->Draw("Q_depoTotal_thre*0.83>>h4","","same");
	t1->Draw("E_depoTotal_l>>h5","","same");
	h1->GetXaxis()->SetTitle("Energy[MeV]");
	h1->SetLineColor(color2[0]);
	h2->SetLineColor(color2[1]);
	h3->SetLineColor(color2[2]);
	h4->SetLineColor(color2[4]);
	h5->SetLineColor(color2[3]);
	TLegend *leg2 = new TLegend(0.2,0.7, 0.64,0.87);
	leg2->SetNColumns(2);
	leg2->SetBorderSize(0);
	leg2->AddEntry(h1, "Available energy", "l");
	leg2->AddEntry(h2, "Deposit energy", "l");
	leg2->AddEntry(h3, "Deposit charge", "l");
	//	leg2->AddEntry(h4, "Deposit charge detected", "l");
	leg2->AddEntry(h5, "Deposit light detected", "l");
	leg2->Draw();
	if(energy==1)
		h1->GetXaxis()->SetRangeUser(0,1400);
	if(energy==3)
		h1->GetXaxis()->SetRangeUser(1000,3200);
	if(energy==5)
		h1->GetXaxis()->SetRangeUser(1800,5200);
	c1->SaveAs("plot/E_smear_"+lep+Form("_%.0fGeV.C",energy));
	c1->SaveAs("plot/E_smear_"+lep+Form("_%.0fGeV.pdf",energy));


    float E_avail[7]={0}, E_depoList[7]={0};
    float Q_depoList[7]={0}, Q_depoList_thre[7]={0},E_depoList_re[7]={0},E_ly;
    float E_depoList_re_lep[7]={0},E_depoList_re_had[7]={0},E_depoList_re_track[7]={0};
    t1->SetBranchAddress("E_availList",E_avail);
    t1->SetBranchAddress("E_depoList",E_depoList);
    t1->SetBranchAddress("Q_depoList",Q_depoList);
    t1->SetBranchAddress("Q_depoList_thre",Q_depoList_thre);
    t1->SetBranchAddress("E_depoList_re",E_depoList_re);
    t1->SetBranchAddress("E_depoList_re_lep",E_depoList_re_lep);
    t1->SetBranchAddress("E_depoList_re_had",E_depoList_re_had);
    t1->SetBranchAddress("E_depoList_re_track",E_depoList_re_track);
    t1->SetBranchAddress("E_depoTotal_l",&E_ly);
	double total_entries = t1->GetEntries();

	TCanvas *c3 = new TCanvas("c3","c3",800,600);
	TH1D *h_Q4 = new TH1D("h_Q4","",200,0,6000);
	TH1D *h_Q3 = new TH1D("h_Q3","",200,0,6000);
	TH1D *h_Q2 = new TH1D("h_Q2","",200,0,6000);
	TH1D *h_L1 = new TH1D("h_L1","",200,0,6000);
	TH1D *h_ly_tmp = new TH1D("h_ly_tmp","",200,0,6000);
	TH1D *h_Q1 = new TH1D("h_Q1","",200,0,6000);
	t1->Draw(Form("Q_depoTotal_thre/%f>>h_Q1",0.58),"","");
	h_Q1->SetLineColor(color[0]);
	//h5->SetLineColor(kGreen);	


	double PCE = 180./25000;
	for(int k=0;k<total_entries;++k){
		t1->GetEntry(k);
		//double nPE = E_ly*180;
		double nPE = E_ly*1e6/19.5*PCE;
		double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
		double E_ly_d = nPE_random/PCE*19.5/1e6;
		h_ly_tmp->Fill(E_ly_d);
	}
	cout<<h_ly_tmp->GetMean()<<"  "<<E_input<<endl;
	cout<<"light scale at "<<E_input<<" = "<<h_ly_tmp->GetMean()/E_input<<endl;
	for(int i=0;i<total_entries;++i){
		t1->GetEntry(i);
		double E_rec_Q2=0;
		double E_rec_Q3=0;
		double E_rec_Q4=0;
		//double nPE = E_ly*180;
		double nPE = E_ly*1e6/19.5*PCE;
		double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
		double E_ly_d = nPE_random/PCE*19.5/1e6; //MeV
		h_L1->Fill(E_ly_d/h_ly_tmp->GetMean()*E_input);
		//h_ly->Fill(E_ly_d);
		double lep_fac = 0.57;
		double had_fac = 0.24;
		//double had_fac = 0.19;
		//fill E_availList: 0 electron, 6 muon, 1 proton, 2 neutron, 3 pi+-, 4 pi0, 5 others.
		for(int j=0;j<7;j++){
			if(j==0){
				E_rec_Q2 +=Q_depoList_thre[j]/0.66;
				//				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				//				E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else if(j==1){
				E_rec_Q2 +=Q_depoList_thre[j]/0.37;
				//E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				//E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else if(j==2){
				E_rec_Q2 +=Q_depoList_thre[j]/0.37;
				//E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				//E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac)/0.97;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac)/0.97;
			}else if(j==3){
				E_rec_Q2 +=Q_depoList_thre[j]/0.37;
				//E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				//E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac)/0.87;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac)/0.87;
			}else if(j==4){
				E_rec_Q2 +=Q_depoList_thre[j]/0.66;
				//E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/lep_fac;
				//E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/lep_fac;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/lep_fac;
				E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/lep_fac;
			}else if(j==5){
				E_rec_Q2 +=Q_depoList_thre[j]/0.37;
				//E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				//E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*0.66/lep_fac+E_depoList_re_had[j]*0.41/had_fac;
				E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else{
				E_rec_Q2 +=Q_depoList_thre[j]/0.66;
				E_rec_Q3+=E_avail[j];
				E_rec_Q4+=E_avail[j];

			}
		}
		h_Q3->Fill(E_rec_Q3);
		h_Q4->Fill(E_rec_Q4);
		h_Q2->Fill(E_rec_Q2);
		//	cout<<E_rec_Q3<<endl;
	}
	h_Q4->SetLineColor(kBlack);
	h_Q3->SetLineColor(color[2]);
	h_Q2->SetLineColor(color[1]);
	h_Q3->GetXaxis()->SetTitle("Energy[MeV]");	
	if(energy==1)
		h_Q3->GetXaxis()->SetRangeUser(200,1500);	
	h_Q3->GetYaxis()->SetRangeUser(0,3000);	
	if(energy==3)
		h_Q3->GetXaxis()->SetRangeUser(1500,3500);	
	//h_Q3->GetYaxis()->SetRangeUser(0,300);	
	if(energy==5)
		h_Q3->GetXaxis()->SetRangeUser(2500,6000);	
	//h_Q3->GetYaxis()->SetRangeUser(0,170);	
	h_Q3->Draw("");
	h_L1->SetLineColor(color[3]);
	//	h_Q4->Draw("same");
	h_Q2->Draw("same");
	h_L1->Draw("same");
	h_Q1->Draw("same");	
	cout<<h5->GetMean()<<endl;
	cout<<h_Q4->GetMean()<<endl;
	gPad->SetGrid();
	TLegend *leg = new TLegend(0.2,0.60, 0.5,0.87);
	leg->SetBorderSize(0);
	leg->AddEntry(h_Q1, "Q1", "l");
	leg->AddEntry(h_Q2, "Q2", "l");
	leg->AddEntry(h_Q3, "Q3", "l");
	//	leg->AddEntry(h_Q4, "M4", "l");
	leg->AddEntry(h_L1, "L1", "l");
	leg->Draw();
	cout<<h_Q3->GetMean()<<endl;
	c3->SaveAs("plot/E_rec_"+lep+Form("_%.0fGeV.pdf",energy));
	c3->SaveAs("plot/E_rec_"+lep+Form("_%.0fGeV.C",energy));

}
