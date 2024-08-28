void normal(TH2D* hmatrix, vector<vector<double>> &result){
	int Nx =  hmatrix->GetNbinsX();
	int Ny =  hmatrix->GetNbinsY();
	for (int i=1;i<=Nx;i++){
		TH1D *h1 = hmatrix->ProjectionY("proj",i,i);
		if(h1->Integral()!=0){
			h1->Scale(1./h1->Integral());
			for(int j=1;j<=Ny;j++){
				result[i][j] = h1->GetBinContent(j);
			}
		}else{
			for(int j=1;j<=Ny;j++){
				result[i][j] = 0;
			}
		}
		delete h1;  
	}
}


void normalize(){
TFile *fmatrix = new TFile("dat/RespondsMatrix_nue.root","read");

TH2D *h_matrix[5];
h_matrix[0] = (TH2D*)fmatrix->Get("h_6");
h_matrix[1] = (TH2D*)fmatrix->Get("h_re_2");
h_matrix[2] = (TH2D*)fmatrix->Get("h_re_3");
h_matrix[3] = (TH2D*)fmatrix->Get("h_re_4");
h_matrix[4] = (TH2D*)fmatrix->Get("h_ly");

vector<vector<double>> normalized_vec(99,vector<double>(80,0));
normal(h_matrix[2],normalized_vec);

ofstream outfile;
outfile.open("smear_matrix.dat");
outfile<<"energy(#app_nue_sig)<"<<endl;
outfile<<"@energy="<<endl;
for(int j=0;j<80;j++){
outfile<<"{0,	98	";
//outfile<<"0	98	";
for(int i=0;i<99;i++){
outfile<<", "<<normalized_vec[i][j]<<"\t";
//outfile<<" "<<normalized_vec[i][j]<<"\t";
}
if(i<98)
outfile<<"}:"<<endl;
else
outfile<<"};"<<endl;
//outfile<<endl;

}
outfile<<">";
outfile.close();

}

