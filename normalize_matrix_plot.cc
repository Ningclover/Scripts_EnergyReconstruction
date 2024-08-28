TH2D *normal(TH2D* hmatrix){
	TH2D *h_norm = (TH2D*)hmatrix->Clone("h_norm");
	h_norm->SetDirectory(0);
	h_norm->Reset();

	int Nx =  hmatrix->GetNbinsX();
	int Ny =  hmatrix->GetNbinsY();
	for (int i=1;i<=Nx;i++){
		TH1D *h1 = hmatrix->ProjectionY("proj",i,i);
		
		if(h1->Integral()!=0){
			h1->Scale(1./h1->Integral());
			for(int j=1;j<=Ny;j++){
				double val = h1->GetBinContent(j);
				h_norm->SetBinContent(i,j,val);
			}
		}else{
			for(int j=1;j<=Ny;j++){
				h_norm->SetBinContent(i,j,0);
			}
		}
		delete h1;  
	}

return h_norm; 
}


void normalize_matrix_plot(){

TFile *fmatrix = new TFile("dat/RespondsMatrix_nue.root","read");

TH2D *h_matrix[5];
TH2D *h_matrix_norm[5];
h_matrix[0] = (TH2D*)fmatrix->Get("h_6");
h_matrix[1] = (TH2D*)fmatrix->Get("h_re_2");
h_matrix[2] = (TH2D*)fmatrix->Get("h_re_3");
h_matrix[3] = (TH2D*)fmatrix->Get("h_re_4");
h_matrix[4] = (TH2D*)fmatrix->Get("h_ly");

TString name[]={"Q1","Q2","Q3","Q4","L1"};

TCanvas *c1 = new TCanvas("c1","c1",800,600);

TLatex text;
    text.SetTextFont(133);
    text.SetTextSize(35);


for(int i=0;i<5;i++){
	h_matrix_norm[i] = normal(h_matrix[i]);
	h_matrix_norm[i]->GetXaxis()->SetTitle("E_{input} [MeV]");
	h_matrix_norm[i]->GetYaxis()->SetTitle("E_{rec} [MeV]");
	h_matrix_norm[i]->GetXaxis()->SetTitleFont(132);
	h_matrix_norm[i]->GetYaxis()->SetTitleFont(132);
	h_matrix_norm[i]->GetXaxis()->SetLabelFont(132);
	h_matrix_norm[i]->GetYaxis()->SetLabelFont(132);
	h_matrix_norm[i]->GetXaxis()->CenterTitle();
	h_matrix_norm[i]->GetYaxis()->CenterTitle();
	h_matrix_norm[i]->Draw("colz");
	text.DrawLatex(1000,5000,name[i]);
	c1->SaveAs("plot/Res_matx_"+name[i]+".pdf");

}



}

