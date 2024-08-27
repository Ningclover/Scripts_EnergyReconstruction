TH1D *smearflux(TH1D* hflux,TH2D* hmatrix ){
	int Nx = hflux->GetNbinsX();
	//TH1D *hout = (TH1D*)hflux->Clone();
	TString name = TString(hflux->GetName())+TString(hmatrix->GetName());
	TH1D *hout = new TH1D(name,"",48,0,6000);
	hout->Reset();
	for (int i=1;i<=Nx;i++){
		double energy = hflux->GetBinCenter(i)*1000;
		double weight = hflux->GetBinContent(i);
		int bin = hmatrix->GetXaxis()->FindBin(energy);
		TH1D *h1 = hmatrix->ProjectionY("proj",bin,bin);
		if(h1->Integral()==0) continue;
		//if(h1->Integral()!=h1->GetEntries())cout<<h1->Integral()<<"  "<<h1->GetEntries()<<endl;
		h1->Scale(weight/h1->Integral());
		hout->Add(h1);
		delete h1;  
	}
	return hout;
}

TH1D *flux2MeV(TH1D* hflux){
	int Nx = hflux->GetNbinsX();
	TString name = TString(hflux->GetName()+TString("MeV"));
	TH1D *hout = new TH1D(name,"",48,0,6000);
	hout->Reset();
	for (int i=1;i<=Nx;i++){
		hout->SetBinContent(i,hflux->GetBinContent(i));
	}
	return hout;
}

TH1D *cuthist(TH1D* hh,int bin_low, int bin_high){
	int Nx = hh->GetNbinsX();
	TH1D *hout = new TH1D("hout2","",48,0,6000);
	for (int i=1;i<=Nx;i++){
		if(i>=bin_low && i<bin_high)
			hout->SetBinContent(i,hh->GetBinContent(i));
	}
	return hout;
}

double chi2(TH1D * pdf, TH1D *data){
	double value=0;
	int nbins = pdf->GetNbinsX();

	for(int i=1;i<=nbins;i++){
		double npdf = pdf->GetBinContent(i);
		double ndata = data->GetBinContent(i);
		if(ndata>0){
			double value1 = log(TMath::Poisson(ndata,npdf));
			double value2 = log(TMath::Poisson(ndata,ndata));
			value += value1 - value2;
			//cout<<i<<"  "<<pdf->GetBinCenter(i)<<"  bin: "<<ndata<<"   "<<npdf<<endl;
			//cout<<"poisson: "<<value1<<"   "<<value2<<endl;
			//cout<<"***** "<<i<<"   "<<value<<endl;
		}
	}
	return -2*value;
}

void smear_dune_flux(){

	double pi=3.1415926;
	double delta[] = {pi/2,0,-pi/2};
	//double delta[] = {-pi,-pi*3/4,-pi/2,-pi/4,0,pi/4,pi/2,pi*3/4,pi};
	const int NN=sizeof(delta)/sizeof(delta[0]);
	double delta_degree[NN] = {0};

	TFile *fmatrix = new TFile("RespondsMatrix_nue.root","read");

	TH2D *h_matrix[5];
	h_matrix[0] = (TH2D*)fmatrix->Get("h_6");
	h_matrix[1] = (TH2D*)fmatrix->Get("h_re_2");
	h_matrix[2] = (TH2D*)fmatrix->Get("h_re_3");
	h_matrix[3] = (TH2D*)fmatrix->Get("h_re_4");
	h_matrix[4] = (TH2D*)fmatrix->Get("h_ly");
	int color[5] ={ kOrange, kGreen, kRed,kBlack ,kBlue}; 

	TFile *fspec = new TFile("dune_flux_2.root","read");
	TFile *fspec_inv = new TFile("dune_flux_inverse.root","read");
	TH1D *h_spec[NN];
	TH1D *h_spec_inv[NN];
	TH1D *h_spec_smear[NN][5];
	TH1D *h_spec_inv_smear[NN][5];
	TH1D *h_spec_smear_1p[NN][5];
	TH1D *h_spec_smear_2p[NN][5];
	TH1D *h_spec_smear_inv_1p[NN][5];
	TH1D *h_spec_smear_inv_2p[NN][5];
	for(int i=0;i<NN;i++){
		h_spec[i] = (TH1D*)fspec->Get(Form("hOsc_%.2f",delta[i]));
		h_spec_inv[i] = (TH1D*)fspec_inv->Get(Form("hOsc_%.2f",delta[i]))->Clone(Form("hOsc_%.2f_inv",delta[i]));
		delta_degree[i] = delta[i]*180/3.14;
		for(int j=0;j<5;j++){
			h_spec_smear[i][j] = smearflux(h_spec[i],h_matrix[j]);
			h_spec_inv_smear[i][j] = smearflux(h_spec_inv[i],h_matrix[j]);
		}
	}

	TCanvas *c1 = new TCanvas("c1","c1",1);
	gPad->SetGrid();
	gStyle->SetOptStat(0);
	h_spec_smear[0][0]->Draw("hist");
	h_spec_smear[0][0]->GetXaxis()->SetRangeUser(0,6000);
	h_spec_smear[0][0]->GetXaxis()->SetTitle("Energy[MeV]");
	h_spec_smear[0][0]->GetYaxis()->SetRangeUser(0,50);
	h_spec_smear[0][0]->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
	h_spec_smear[0][0]->GetYaxis()->SetTitleOffset(1);
	h_spec_smear[0][0]->GetYaxis()->CenterTitle();
	h_spec_smear[1][0]->Draw("same hist");
	h_spec_smear[2][0]->Draw("same hist");
	h_spec_smear[0][0]->SetLineColor(2);
	h_spec_smear[1][0]->SetLineColor(1);
	h_spec_smear[2][0]->SetLineColor(4);

	TLegend *leg2 = new TLegend(0.65,0.60, 0.87,0.87);
	leg2->AddEntry(h_spec_smear[0][0], " #delta=#pi/2", "l");
	leg2->AddEntry(h_spec_smear[1][0], " #delta=0", "l");
	leg2->AddEntry(h_spec_smear[2][0], " #delta=-#pi/2", "l");
	leg2->SetBorderSize(0);
	leg2->Draw();
	c1->SaveAs("plot/nue_cc_spec_smear.pdf");
		c1->SaveAs("plot/nue_cc_spec_smear.C");

	TCanvas *c2 = new TCanvas("c2","c2",1);
	gPad->SetGrid();
	gStyle->SetOptStat(0);
	TH1D *h0 = flux2MeV(h_spec[0]);
	TH1D *h1 = flux2MeV(h_spec[1]);
	TH1D *h2 = flux2MeV(h_spec[2]);
	h0->Draw("hist");
	h0->GetXaxis()->SetRangeUser(0,6000);
	h0->GetXaxis()->SetTitle("Energy[GeV]");
	h0->GetYaxis()->SetRangeUser(0,50);
	h0->GetYaxis()->SetTitle("#nu_{e}CC Events / (40 kTon #upoint y #upoint 1.2 MW)");
	h0->GetYaxis()->SetTitleOffset(1);
	h0->GetYaxis()->CenterTitle();
	h1->Draw("same hist");
	h2->Draw("same hist");
	h0->SetLineColor(2);
	h1->SetLineColor(1);
	h2->SetLineColor(4);
	leg2->Draw();
	c2->SaveAs("plot/nue_cc_spec.pdf");
	c2->SaveAs("plot/nue_cc_spec.C");


}

