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
		}
	}
	return -2*value;
}

void significant(){
double pi=3.1415926;
//double delta[] = {pi/2,pi/4,0,-pi/4,-pi/2};
double delta[] = {-pi,-pi*3/4,-pi/2,-pi/4,0,pi/4,pi/2,pi*3/4,pi};
const int NN=sizeof(delta)/sizeof(delta[0]);
double delta_degree[NN] = {0};

TFile *fmatrix = new TFile("RespondsMatrix.root","read");

TH2D *h_matrix[5];
h_matrix[0] = (TH2D*)fmatrix->Get("h_6");
h_matrix[1] = (TH2D*)fmatrix->Get("h_re_2");
h_matrix[2] = (TH2D*)fmatrix->Get("h_re_3");
h_matrix[3] = (TH2D*)fmatrix->Get("h_re_4");
h_matrix[4] = (TH2D*)fmatrix->Get("h_ly");
int color[5] ={ kOrange, kGreen, kRed,kBlack ,kBlue}; 

TFile *fspec = new TFile("dune_flux_2.root","read");
TH1D *h_spec[NN];
TH1D *h_spec_smear[NN][5];
TH1D *h_spec_smear_1p[NN][5];
TH1D *h_spec_smear_2p[NN][5];
for(int i=0;i<NN;i++){
	h_spec[i] = (TH1D*)fspec->Get(Form("hOsc_%.2f",delta[i]));
	delta_degree[i] = delta[i]*180/3.14;
	for(int j=0;j<5;j++){
		h_spec_smear[i][j] = smearflux(h_spec[i],h_matrix[j]);
	}
}
int cut1 = h_spec_smear[0][0]->FindBin(990);
int cut2 = h_spec_smear[0][1]->FindBin(1100);

TCanvas *c1 = new TCanvas("c1","c1",1);
		h_spec_smear[0][0]->Draw("a");
for(int j=0;j<NN;j++){
	h_spec_smear_1p[j][0] = cuthist(h_spec_smear[j][0],0,cut1+1);
	h_spec_smear_2p[j][0] = cuthist(h_spec_smear[j][0],cut1+1,49);
}
	h_spec_smear_1p[0][0]->Draw("hist");
	h_spec_smear_1p[0][0]->SetLineColor(color[0]);

for(int j=1;j<5;j++){
	for(int i=0;i<NN;i++){
	h_spec_smear_1p[i][j] = cuthist(h_spec_smear[i][j],0,cut2+1);
	h_spec_smear_2p[i][j] = cuthist(h_spec_smear[i][j],cut2+1,49);
	}
	h_spec_smear_1p[0][j]->Draw("same hist");
	h_spec_smear_1p[0][j]->SetLineColor(color[j]);
}


  TLegend *leg2 = new TLegend(0.65,0.60, 0.87,0.87);
    leg2->SetBorderSize(0);
double sen_chi2[5][NN]={0};
TGraph *g1[5];
for(int j=0;j<5;j++){
	for(int i=0;i<NN;i++){
		//sen_chi2[j][i] = chi2(h_spec_smear_2p[i][j],h_spec_smear_2p[0][j]);
		//sen_chi2[j][i] = chi2(h_spec_smear_1p[i][j],h_spec_smear_1p[4][j]);
		//sen_chi2[j][i] = chi2(h_spec_smear[i][j],h_spec_smear[4][j]);
		//double chi_0 = chi2(h_spec_smear[4][j],h_spec_smear[i][j]);
		//double chi_0 = chi2(h_spec_smear_1p[4][j],h_spec_smear_1p[i][j]);
		double chi_0 = chi2(h_spec_smear_2p[4][j],h_spec_smear_2p[i][j]);
		//double chi_0=0;
		//double chi_pi = chi2(h_spec_smear[8][j],h_spec_smear[i][j]);
		//double chi_pi = chi2(h_spec_smear_1p[8][j],h_spec_smear_1p[i][j]);
		double chi_pi = chi2(h_spec_smear_2p[8][j],h_spec_smear_2p[i][j]);
		
		//sen_chi2[j][i] = sqrt(abs(sen_chi2[j][i]));
		if(chi_0<chi_pi) 
		sen_chi2[j][i] = sqrt(abs(chi_0));
		else
		sen_chi2[j][i] = sqrt(abs(chi_pi));
		cout<<i<<"  "<<j<<"  "<<sen_chi2[j][i]<<"  "<<chi_0<<"  "<<chi_pi<<endl;
	}
	g1[j] = new TGraph(NN,delta_degree,&sen_chi2[j][0]);
	g1[j]->SetLineColor(color[j]);
	g1[j]->SetLineWidth(2);
		cout<<delta_degree[j]<<"************"<<endl;
}

TCanvas *c2 = new TCanvas("c2","c2",800,600);
g1[0]->GetXaxis()->SetRangeUser(-180,180);
g1[0]->GetXaxis()->SetTitle("#delta_{CP} #circ");
g1[0]->GetYaxis()->SetTitle("#sqrt{#chi ^{2}}");
g1[0]->Draw("Al");
g1[0]->GetYaxis()->SetRangeUser(0,10);
leg2->AddEntry(g1[0], "M1", "l");
g1[1]->Draw("same l");
leg2->AddEntry(g1[1], "M2", "l");
g1[2]->Draw("same l");
leg2->AddEntry(g1[2], "M3", "l");
//g1[3]->Draw("same l");
//leg2->AddEntry(g1[3], "M4", "l");
g1[4]->Draw("same l");
leg2->AddEntry(g1[4], "Light", "l");

leg2->Draw();

//	double chi2_try = chi2(h_spec_smear[0][0],h_spec_smear[4][0]);
//	 cout<<chi2_try<<endl;

	
}

