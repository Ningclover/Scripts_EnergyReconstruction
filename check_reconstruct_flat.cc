	
TH1D *smearflux(TH1D* hflux,TH2D* hmatrix ,int flag=0){
int Nx = hflux->GetNbinsX();
//TH1D *hout = (TH1D*)hflux->Clone();
TH1D *hout = new TH1D("hout","",48,0,6000);
hout->Reset();
for (int i=1;i<=Nx;i++){
	double energy = hflux->GetBinCenter(i)*1000;
	double weight = hflux->GetBinContent(i);
	int bin = hmatrix->GetXaxis()->FindBin(energy);
	TH1D *h1 = hmatrix->ProjectionY("proj",bin,bin);
	if(h1->Integral()==0) continue;
	h1->Scale(weight/h1->Integral());
	hout->Add(h1);	
}
return hout;
}

TH1D *Drawproject(TH2D* hmatrix ,TString name){
int bin = hmatrix->GetXaxis()->FindBin(1200);
TH1D *hh = hmatrix->ProjectionY(name,bin,bin);
	cout<<"mean = "<<hh->GetMean()<<endl;
	return hh;
}

TH1D *changefluxDim(TH1D* hflux){
int Nx = hflux->GetNbinsX();
//TH1D *hout = (TH1D*)hflux->Clone();
TH1D *hout = new TH1D("hout","",48,0,6000);
hout->Reset();
for (int i=1;i<=Nx;i++){
	double energy = hflux->GetBinCenter(i)*1000;
	double weight = hflux->GetBinContent(i);
	int bin = hout->GetXaxis()->FindBin(energy);
	hout->SetBinContent(bin,weight);

}
return hout;
}

void check_reconstruct_flat(){

			gStyle->SetOptStat(0);
	TChain *t1 = new TChain("Sim");
	int color[]={kBlack,kBlue,kGreen+2,kGreen-7,kAzure+6,kOrange};
//	t1->Add("/data2/users/xning/output/thre_track_leha_edep_0.5-5_numu_10k_lean.root");
//	t1->Add("/data2/users/xning/output/thre_track_leha_edep_0.5-5_numu_10k.root");
	t1->Add("/data2/users/xning/output/thre_track_leha_edep_0.5-5_nue_10k_lean.root");
	t1->Add("/data2/users/xning/output/thre_track_leha_edep_0.5-5_nue_10k.root");
	t1->Add("/data2/users/xning/output/thre_track_leha_edep.22862.root");
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	TH1D *h1 = new TH1D("h1","",100,0,6000);
	TH1D *h2 = new TH1D("h2","",100,0,6000);
	TH1D *h3 = new TH1D("h3","",100,0,6000);
	TH1D *h4 = new TH1D("h4","",100,0,6000);
	TH1D *h5 = new TH1D("h5","",100,0,6000);
	TH1D *h6 = new TH1D("h6","",100,0,6000);
	t1->Draw("E_avail>>h1");
//	t1->Draw("E_depoTotal>>h2","","same");
//	t1->Draw("Q_depoTotal>>h3","","same");
//	t1->Draw("Q_depoTotal_thre>>h4","","same");
	//t1->Draw("E_depoTotal_re>>h5","","same");
	h1->SetLineColor(color[0]);
	h2->SetLineColor(color[1]);
	h3->SetLineColor(color[2]);
	h4->SetLineColor(color[3]);
	h5->SetLineColor(color[4]);
	h6->SetLineColor(color[5]);

	float E_avail[7]={0}, E_depoList[7]={0};
	float E_availTotal;
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
	t1->SetBranchAddress("E_avail",&E_availTotal);
	double total_entries = t1->GetEntries();
	cout<<"total entries = "<<total_entries<<endl;
	t1->GetEntry(5);
	int i=0;
	TH1D *h_E_re[7];
	TH1D *h_Q[7];
	TH1D *h_Q_thre[7];
	TH1D *h_E[7];
	TCanvas *c2[7]; 
	double upper[]={3000,3000,800,500,2500,10,2500};
	//fill E_availList: 0 electron, 6 muon, 1 proton, 2 neutron, 3 pi+-, 4 pi0, 5 others.
//	for(int j=0;j<7;j++){
//			c2[j] = new TCanvas(Form("c2_%d",j),"c2",800,600);
//			TH2D *h_axis = new TH2D("h_re_1","",1,0.1,1.3,1,0,upper[j]);
//			h_axis->Draw("");
//			h_axis->SetTitle(Form("%d",j));
//			h_axis->GetXaxis()->SetTitle("Ratio");
//			h_E_re[j] = new TH1D(Form("h_E_re_%d",j),"",100,0.05,2);
//			h_Q[j] = new TH1D(Form("h_Q_%d",j),"",100,0.05,2);
//			h_Q_thre[j] = new TH1D(Form("h_Q_thre_%d",j),"",100,0.05,2);
//			h_E[j] = new TH1D(Form("h_E_%d",j),"",100,0.05,2);
//			h_E_re[j]->SetLineColor(color[4]);
//			h_Q_thre[j]->SetLineColor(color[3]);
//			h_E[j]->SetLineColor(color[1]);
//			h_Q[j]->SetLineColor(color[2]);
//			t1->Draw(Form("Q_depoList_thre[%d]/E_availList[%d]>>h_Q_thre_%d",j,j,j),"","same");
//			t1->Draw(Form("Q_depoList[%d]/E_availList[%d]>>h_Q_%d",j,j,j),"","same");
//			//t1->Draw(Form("Q_depoList[%d]/E_depoList[%d]>>h_Q_%d",j,j,j),"","same");
//			t1->Draw(Form("E_depoList[%d]/E_availList[%d]>>h_E_%d",j,j,j),"","same");
//			if(j==4){
//			t1->Draw(Form("(E_depoList_re_track[%d]+E_depoList_re_lep[%d]*0.66/0.57+E_depoList_re_had[%d]*0.41/0.57)/E_availList[%d]>>h_E_re_%d",j,j,j,j,j),"","same");
//			}else{
//			t1->Draw(Form("(E_depoList_re_track[%d]+E_depoList_re_lep[%d]*0.66/0.57+E_depoList_re_had[%d]*0.41/0.21)/E_availList[%d]>>h_E_re_%d",j,j,j,j,j),"","same");
//}
//			double mean1,mean2,mean3,mean4;
//			double prob[]={0.5};
//			h_Q[j]->GetQuantiles(1,&mean1,prob);
//			h_E_re[j]->GetQuantiles(1,&mean2,prob);
//			//cout<<"mean: "<<j<<" "<<h_Q[j]->GetMean()<<"  "<<h_Q_thre[j]->GetMean()<<"  "<<h_E_re[j]->GetMean()<<"  "<<h_E[j]->GetMean()<<endl;
//			cout<<"mean: "<<j<<" "<<mean1<<"  "<<mean2<<endl;
//	}

	int NbinsX = 48;
	double lowerX = 0, upperX = 6000;
	int NbinsY= NbinsX;
	double lowerY = lowerX, upperY = upperX;
	cout<<NbinsX<<"  "<<lowerX<<"  "<<upperX<<endl;
	TCanvas *c3 = new TCanvas("c3","c3",800,600);
	TH2D *h_6 = new TH2D("h_6","",NbinsX,lowerX,upperX,NbinsY,lowerY,upperY);
	TH2D *h_re = new TH2D("h_re_4","",NbinsX,lowerX,upperX,NbinsY,lowerY,upperY);
	TH2D *h_re_2 = new TH2D("h_re_2","",NbinsX,lowerX,upperX,NbinsY,lowerY,upperY);
	TH2D *h_re_3 = new TH2D("h_re_3","",NbinsX,lowerX,upperX,NbinsY,lowerY,upperY);
	TH2D *h_ly = new TH2D("h_ly","",NbinsX,lowerX,upperX,NbinsY,lowerY,upperY);
	TH1D *h_ly_tmp = new TH1D("h_ly_tmp","",NbinsX,lowerX,upperX);

for(int k=0;k<total_entries;++k){
		t1->GetEntry(k);
        double nPE = E_ly*180;
        double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
        double E_ly_d = nPE_random/180;
        h_ly_tmp->Fill(E_ly_d);
}
	for(int i=0;i<total_entries;++i){
		t1->GetEntry(i);
		double E_reconstruct_HL=0;
		double E_reconstruct=0;
		double E_reconstruct_2=0;
       	double nPE = E_ly*180;
        double nPE_random = gRandom->Gaus(nPE,sqrt(nPE));
        double E_ly_d = nPE_random/180;
        //h_ly->Fill(E_availTotal,E_ly_d/h_ly_tmp->GetMean()*E_availTotal);
        h_ly->Fill(E_availTotal,E_ly_d/0.42);
        //h_ly->Fill(E_ly_d);
		double lep_fac = 0.57;
		double had_fac = 0.24;
		//fill E_availList: 0 electron, 6 muon, 1 proton, 2 neutron, 3 pi+-, 4 pi0, 5 others.
		for(int j=0;j<7;j++){
			if(j==0){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.66;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_reconstruct_2+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else if(j==1){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.37;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_reconstruct_2+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else if(j==2){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.37;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_reconstruct_2+=(E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac)/0.97;
			}else if(j==3){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.37;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_reconstruct_2+=(E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac)/0.87;
			}else if(j==4){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.66;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/lep_fac;
				E_reconstruct_2+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/lep_fac;
			}else if(j==5){
				E_reconstruct_HL +=Q_depoList_thre[j]/0.37;
				E_reconstruct+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
				E_reconstruct_2+=E_depoList_re_track[j]+E_depoList_re_lep[j]/lep_fac+E_depoList_re_had[j]/had_fac;
			}else{
				E_reconstruct_HL +=Q_depoList_thre[j]/0.66;
				E_reconstruct+=E_avail[j];
				E_reconstruct_2+=E_avail[j];

			}
		}
		h_re_2->Fill(E_availTotal,E_reconstruct_HL);
		h_re_3->Fill(E_availTotal,E_reconstruct);
		h_re->Fill(E_availTotal,E_reconstruct_2);
	//	cout<<E_reconstruct<<endl;
	}
//	gPad->SetLogz();
	c3->SaveAs("/home/xning/Pic/a.pdf[");
	t1->Draw("Q_depoTotal_thre/0.7:E_avail>>h_6","","colz");
	h_6->SetTitle("Method 1");
	h_6->GetXaxis()->SetTitle("E_input [GeV]");
	h_6->GetYaxis()->SetTitle("E_rec [GeV]");
	c3->SaveAs("/home/xning/Pic/a.pdf") ;
	h_re_2->Draw("colz");              
	h_re_2->SetTitle("Method 2");
	h_re_2->GetXaxis()->SetTitle("E_input [GeV]");
	h_re_2->GetYaxis()->SetTitle("E_rec [GeV]");
	c3->SaveAs("/home/xning/Pic/a.pdf") ;
	h_re_3->Draw("colz");               
	h_re_3->SetTitle("Method 3");
	h_re_3->GetXaxis()->SetTitle("E_input [GeV]");
	h_re_3->GetYaxis()->SetTitle("E_rec [GeV]");
	c3->SaveAs("/home/xning/Pic/a.pdf") ;
	h_re->Draw("colz");                 
	h_re->SetTitle("Method 4");
	h_re->GetXaxis()->SetTitle("E_input [GeV]");
	h_re->GetYaxis()->SetTitle("E_rec [GeV]");
	c3->SaveAs("/home/xning/Pic/a.pdf") ;
	h_ly->Draw("colz");                 
	h_ly->SetTitle("Light");
	h_ly->GetXaxis()->SetTitle("E_input [GeV]");
	h_ly->GetYaxis()->SetTitle("E_rec [GeV]");
	c3->SaveAs("/home/xning/Pic/a.pdf") ;
	c3->SaveAs("/home/xning/Pic/a.pdf]");
TFile *fout =  new TFile("RespondsMatrix.root","recreate");
h_6->Write();
h_re_2->Write();
h_re_3->Write();
h_re->Write();
h_ly->Write();
fout->Close();

//exit(0);	
TFile *f1= new TFile("dune_flux.root","read");
TH1D *h_flux_1 = (TH1D*)f1->Get("hOsc1");
TH1D *h_flux_2 = (TH1D*)f1->Get("hOsc2");
TH1D *h_flux_3 = (TH1D*)f1->Get("hOsc3");
TH1D *fflux_1 = changefluxDim(h_flux_1);
TH1D *fflux_2 = changefluxDim(h_flux_2);
TH1D *fflux_3 = changefluxDim(h_flux_3);
fflux_1->SetLineColor(kBlue);
fflux_2->SetLineColor(kBlue);
fflux_3->SetLineColor(kBlue);
fflux_1->SetLineStyle(7);
fflux_2->SetLineStyle(7);
fflux_3->SetLineStyle(7);

TH1D *fout_1_6 = smearflux(h_flux_1,h_6);
TH1D *fout_2_6 = smearflux(h_flux_2,h_6);
TH1D *fout_3_6 = smearflux(h_flux_3,h_6);
fout_1_6->SetLineColor(1);
fout_2_6->SetLineColor(2);
fout_3_6->SetLineColor(3);

TH1D *fout_1_ly = smearflux(h_flux_1,h_ly);
TH1D *fout_2_ly = smearflux(h_flux_2,h_ly);
TH1D *fout_3_ly = smearflux(h_flux_3,h_ly);
fout_1_ly->SetLineColor(1);
fout_2_ly->SetLineColor(2);
fout_3_ly->SetLineColor(3);

TH1D *fout_1_re_2 = smearflux(h_flux_1,h_re_2);
TH1D *fout_2_re_2 = smearflux(h_flux_2,h_re_2);
TH1D *fout_3_re_2 = smearflux(h_flux_3,h_re_2);
fout_1_re_2->SetLineColor(1);
fout_2_re_2->SetLineColor(2);
fout_3_re_2->SetLineColor(3);

TH1D *fout_1_re_3 = smearflux(h_flux_1,h_re_3);
TH1D *fout_2_re_3 = smearflux(h_flux_2,h_re_3);
TH1D *fout_3_re_3 = smearflux(h_flux_3,h_re_3);
fout_1_re_3->SetLineColor(1);
fout_2_re_3->SetLineColor(2);
fout_3_re_3->SetLineColor(3);

  TLegend *leg2 = new TLegend(0.65,0.60, 0.87,0.87);
	leg2->SetBorderSize(0);
  leg2->AddEntry(fout_1_ly, " #delta=0", "l");
  leg2->AddEntry(fout_2_ly,   " #delta=#pi/2", "l");
  leg2->AddEntry(fout_3_ly,   " #delta=-#pi/2", "l");
TCanvas *c4 = new TCanvas("c4","c4",800,600);
c4->SaveAs("/home/xning/Pic/b.pdf[");
fout_3_6->Draw("hist");
fout_3_6->GetXaxis()->SetTitle("Energy [MeV]");
fout_3_6->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
fout_1_6->Draw("hist same");
fout_2_6->Draw("hist same");
  leg2->Draw();
//fflux_1->Draw("hist same");
//fflux_2->Draw("hist same");
//fflux_3->Draw("hist same");
c4->SaveAs("/home/xning/Pic/b.pdf");
fout_3_ly->Draw("hist");
fout_3_ly->GetXaxis()->SetTitle("Energy [MeV]");
fout_3_ly->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
fout_1_ly->Draw("hist same");
fout_2_ly->Draw("hist same");
  leg2->Draw();
//fflux_1->Draw("hist same");
//fflux_2->Draw("hist same");
//fflux_3->Draw("hist same");
c4->SaveAs("/home/xning/Pic/b.pdf");
fout_3_re_2->Draw("hist");
fout_3_re_2->GetXaxis()->SetTitle("Energy [MeV]");
fout_3_re_2->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
fout_1_re_2->Draw("hist same");
fout_2_re_2->Draw("hist same");
  leg2->Draw();
//fflux_1->Draw("hist same");
//fflux_2->Draw("hist same");
//fflux_3->Draw("hist same");
c4->SaveAs("/home/xning/Pic/b.pdf");
fout_3_re_3->Draw("hist");
fout_3_re_3->GetXaxis()->SetTitle("Energy [MeV]");
fout_3_re_3->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
fout_1_re_3->Draw("hist same");
fout_2_re_3->Draw("hist same");
  leg2->Draw();
//fflux_1->Draw("hist same");
//fflux_2->Draw("hist same");
//fflux_3->Draw("hist same");
c4->SaveAs("/home/xning/Pic/b.pdf");
c4->SaveAs("/home/xning/Pic/b.pdf]");


TCanvas *c5 = new TCanvas("c5","c5",800,600);
TH1D *h_1GeV_ly = Drawproject(h_ly,"aa"); 
TH1D *h_1GeV_6 = Drawproject(h_6,"bb"); 
TH1D *h_1GeV_re_3 = Drawproject(h_re_3,"cc"); 
TH1D *h_1GeV_re_2 = Drawproject(h_re_2,"dd"); 
h_1GeV_6->SetLineColor(kOrange);
h_1GeV_ly->SetLineColor(kBlue);
h_1GeV_re_3->SetLineColor(kRed);
h_1GeV_re_2->SetLineColor(kGreen);
cout<<h_1GeV_6->GetMean()<<endl;
cout<<h_1GeV_ly->Integral()<<endl;
cout<<h_1GeV_re_3->Integral()<<endl;
cout<<h_1GeV_re_2->Integral()<<endl;
h_1GeV_re_3->GetXaxis()->SetRangeUser(500,2000);
h_1GeV_re_3->Draw("hist");
h_1GeV_6->Draw("hist same");
h_1GeV_ly->Draw("hist same");
h_1GeV_re_2->Draw("hist same");

}



