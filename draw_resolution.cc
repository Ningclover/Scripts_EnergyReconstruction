void draw_resolution(){
	TFile *file_TDR = new TFile("/home/xning/script/smear_m_nue_sig.root","read");
	TH2D *h_TDR = (TH2D*)file_TDR->Get("test");
	TFile *file[14];
	TTree *tree[14];
	TH1D *h_Q1[14];
	TH1D *h_Q4[14];
	TH1D *h_Q2[14];
	TH1D *h_Q3[14];
	TH1D *hre_tmp_3[14];
	TH1D *h_L1[14];
	TH1D *hly_tmp[14];
	//TString KE[] = {"0.5","1","1.5","2","2.5","3","3.5","4","4.5","5"};
	TString KE[] = {"0.5","1.0","1.5","2.0","2.5","3.0","3.5","4.0","4.5","5.0"};
	//TString KE[] = {"0.5","0.6","0.7","0.8","0.9","1","1.5","2","2.5","3","3.5","4","4.5","5"};
	double E[14]={0}, res_Q4[14]={0},res_Q1[14]={0},res_Q2[14]={0},res_L1[14]={0},res_Q3[14]={0},resolution_TDR[14]={0};
	TCanvas *c2 = new TCanvas("c2","c2",800,600);
	for (int i=0;i<10;i++){
		//for (int i=0;i<14;i++){
		double input_E = atof(KE[i]);
		h_Q1[i] = new TH1D(Form("hre_%d",i),"",1000,0,6000);
		h_Q4[i] = new TH1D(Form("hre_2_%d",i),"",1000,0,6000);
		h_Q2[i] = new TH1D(Form("hQ2_%d",i),"",1000,0,6000);
		h_Q3[i] = new TH1D(Form("hre_4_%d",i),"",1000,0,6000);
		hre_tmp_3[i] = new TH1D(Form("hre_tmp_3_%d",i),"",1000,0,6000);
		h_L1[i] = new TH1D(Form("hly_%d",i),"",1000,0,6000);
		hly_tmp[i] = new TH1D(Form("hly_tmp_%d",i),"",1000,0,6000);
		TString name = "/data2/users/xning/output/thre_track_leha_E_edep_"+KE[i]+"_10000_12.root";
		file[i] = new TFile(name,"read");
		tree[i] = (TTree*)file[i]->Get("Sim");
		float E_avail[7]={0}, E_depoList[7]={0};
		float Q_depoList[7]={0}, Q_depoList_thre[7]={0},E_depoList_re[7]={0},E_ly;
		float E_depoList_re_lep[7]={0},E_depoList_re_had[7]={0},E_depoList_re_track[7]={0};
		tree[i]->SetBranchAddress("E_availList",E_avail);
		tree[i]->SetBranchAddress("E_depoList",E_depoList);
		tree[i]->SetBranchAddress("Q_depoList",Q_depoList);
		tree[i]->SetBranchAddress("Q_depoList_thre",Q_depoList_thre);
		tree[i]->SetBranchAddress("E_depoList_re",E_depoList_re);
		tree[i]->SetBranchAddress("E_depoTotal_l",&E_ly);
		tree[i]->SetBranchAddress("E_depoList_re_lep",E_depoList_re_lep);
		tree[i]->SetBranchAddress("E_depoList_re_had",E_depoList_re_had);
		tree[i]->SetBranchAddress("E_depoList_re_track",E_depoList_re_track);
		double total_entries = tree[i]->GetEntries();
		double PCE = 180./25000;
		for(int k=0;k<total_entries;++k){
			double E_Q3=0;
			double E_reconstruct_2=0;
			tree[i]->GetEntry(k);
			//double nPE = E_ly*180;
			double nPE = E_ly*1e6/19.5*PCE;
			double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
			//double E_ly_d = nPE_random/180;
			double E_ly_d = nPE_random/PCE*19.5/1e6;
			hly_tmp[i]->Fill(E_ly_d);

		}
		double factor = hly_tmp[i]->GetMean()/input_E/1000;
		for(int k=0;k<total_entries;++k){
			double E_rec_Q3=0;
			double E_rec_Q4=0;
			double E_rec_Q1=0;
			double E_rec_Q2=0;
			tree[i]->GetEntry(k);
			//double nPE = E_ly*180;
			double nPE = E_ly*1e6/19.5*PCE;
			double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
			double E_ly_d = nPE_random/PCE*19.5/1e6/factor;
			//double E_ly_d = nPE_random/180/factor;
			double lep_fac = 0.57;
			double had_fac = 0.24;
			//double had_fac = 0.19;
			//double lep1 = 0.66;
			//double had1 = 0.41;
			double lep1 = 1;
			double had1 = 1;
			//		if(i>0&&i<5) 
			//		{
			//			lep1=1;
			//			had1=1;
			//		}
			//fill E_availList: 0 electron, 6 muon, 1 proton, 2 neutron, 3 pi+-, 4 pi0, 5 others.
			for(int j=0;j<7;j++){
				E_rec_Q1+=Q_depoList_thre[j]/0.58;
				if(j==0){
					E_rec_Q2 +=Q_depoList_thre[j]/0.66;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/had_fac;
					E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                 E_depoList_re_had[j]*had1/had_fac;
				}else if(j==1){
					E_rec_Q2 +=Q_depoList_thre[j]/0.37;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/had_fac;
					E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                 E_depoList_re_had[j]*had1/had_fac;
				}else if(j==2){
					E_rec_Q2 +=Q_depoList_thre[j]/0.37;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/had_fac;
					E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                E_depoList_re_had[j]*had1/had_fac)/0.97;
				}else if(j==3){
					E_rec_Q2 +=Q_depoList_thre[j]/0.37;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/had_fac;
					E_rec_Q4+=(E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                E_depoList_re_had[j]*had1/had_fac)/0.87;
				}else if(j==4){
					E_rec_Q2 +=Q_depoList_thre[j]/0.66;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/lep_fac;
					E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                 E_depoList_re_had[j]*had1/lep_fac;
				}else if(j==5){
					E_rec_Q2 +=Q_depoList_thre[j]/0.37;
					E_rec_Q3+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                   E_depoList_re_had[j]*had1/had_fac;
					E_rec_Q4+=E_depoList_re_track[j]+E_depoList_re_lep[j]*lep1/lep_fac+                 E_depoList_re_had[j]*had1/had_fac;
				}else{
					E_rec_Q2 +=Q_depoList_thre[j]/0.66;
					E_rec_Q3+=E_avail[j];
					E_rec_Q4+=E_avail[j];

				} 
			}        

			//	cout<<"test"<<E_rec_Q3<<"  "<<E_rec_Q4<<endl;
			h_L1[i]->Fill(E_ly_d);
			h_L1[i]->SetLineColor(kBlue);
			h_Q1[i]->Fill(E_rec_Q1);
			h_Q1[i]->SetLineColor(kOrange);	
			h_Q4[i]->Fill(E_rec_Q4);
			h_Q4[i]->SetLineColor(kBlack);	
			h_Q2[i]->Fill(E_rec_Q2);
			h_Q2[i]->SetLineColor(kGreen);	

			h_Q3[i]->Fill(E_rec_Q3);
			h_Q3[i]->SetLineColor(kRed);	
		}
		h_Q1[i]->Draw("same");
		//h_Q4[i]->Draw("same");
		//h_Q2[i]->Draw("same");
		//h_Q3[i]->Draw("same");
		h_L1[i]->Draw("same");


		E[i]=input_E;
		double E_x = input_E*1000;
		//resolution_TDR[i] = h_TDR_1d->GetStdDev()/h_TDR_1d->GetMean()*100;
		double sigma = h_Q2[i]->GetStdDev();
		cout<<"*** std *** "<<sigma<<" "<<sigma/h_Q2[i]->GetMean()<<endl;
		cout<<"*** mean *** "<<h_L1[i]->GetMean()<<" "<<h_Q1[i]->GetMean()<<endl;
		res_L1[i]=h_L1[i]->GetStdDev()/h_L1[i]->GetMean()*100;
		res_Q1[i]=h_Q1[i]->GetStdDev()/h_Q1[i]->GetMean()*100;
		res_Q4[i]=h_Q4[i]->GetStdDev()/h_Q4[i]->GetMean()*100;
		res_Q2[i]=h_Q2[i]->GetStdDev()/h_Q2[i]->GetMean()*100;
		res_Q3[i]=h_Q3[i]->GetStdDev()/h_Q3[i]->GetMean()*100;
		if(input_E==1){
			cout<<res_Q1[i]<<" || "<<res_Q2[i]<<" || "<<res_Q3[i]<<" || "<<res_Q4[i]<<" || "<<res_L1[i]<<" || "<<resolution_TDR[i]<<endl;
		}
	}

	TH2D *h_axis = new TH2D("h_axis","",1,0,5.5,1,0,20);
	h_axis->GetXaxis()->SetTitle("Energy [GeV]");
	h_axis->GetYaxis()->SetTitle("Resolution [%]");
	h_axis->GetXaxis()->CenterTitle();
	h_axis->GetYaxis()->CenterTitle();
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	gPad->SetGrid();
	int color[]={1,kGreen+2,4,2,6,5};
	TGraph *g1 = new TGraph(10,E,res_Q3);	//Q3
	TGraph *g2 = new TGraph(10,E,res_Q1); //Q1
	TGraph *g3 = new TGraph(10,E,res_Q2); //Q2
	TGraph *g4 = new TGraph(10,E,res_L1); //L1
	TGraph *g5 = new TGraph(10,E,res_Q4);	//Q4
	TGraph *g6 = new TGraph(10,E,resolution_TDR);
	h_axis->Draw("");
	g1->Draw("L same");
//	g1->GetXaxis()->SetTitle("Energy [GeV]");
//	g1->GetYaxis()->SetTitle("Resolution [%]");
	g1->SetLineWidth(2);
	g2->SetLineWidth(2);
	g3->SetLineWidth(2);
	g1->GetYaxis()->SetRangeUser(0,20);
	g2->SetLineColor(color[0]);
	g1->SetLineColor(color[2]);
	g3->SetLineColor(color[1]);
	g3->Draw("same l ");
	g2->Draw("same l ");
	g4->SetLineWidth(2);
	g4->SetLineColor(color[3]);
	g4->Draw("same l");
	g5->SetLineWidth(2);
	g5->SetLineColor(color[4]);
	//g5->Draw("same l");
	g6->SetLineWidth(2);
	g6->SetLineColor(kViolet-2);
	//g6->Draw("same l");

	TLegend *leg = new TLegend(0.6,0.70, 0.87,0.87);
	leg->SetNColumns(2);
	leg->SetBorderSize(0);
	leg->AddEntry(g2, "Q1", "l");
	leg->AddEntry(g3, "Q2", "l");
	leg->AddEntry(g1, "Q3", "l");
	//leg->AddEntry(g5, "Q4", "l");
	leg->AddEntry(g4, "L1", "l");
	leg->Draw();
	c1->SaveAs("plot/resolution.pdf");
	c1->SaveAs("plot/resolution.C");

	}
