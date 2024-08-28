void RL_efield(){
TCanvas *c1 = new TCanvas("c1","c1",800,600);
gPad->SetGrid();
TH2D *h1 = new TH2D("h1","h1",1,0,2,1,0.3,0.9);
h1->Draw("axis");
h1->GetXaxis()->SetTitle("Drift E field[kV/cm]");
h1->GetYaxis()->SetTitle("R_{L}");
h1->GetXaxis()->CenterTitle();
h1->GetYaxis()->CenterTitle();

TH1D *hh1 = new TH1D("hh1","",1,1,1);
hh1->SetLineColor(1);
TH1D *hh2= new TH1D("hh2","",1,1,1);
TH1D *hh3= new TH1D("hh3","",1,1,1);
hh2->SetLineColor(2);
hh3->SetLineColor(4);

TLegend *leg3 = new TLegend(0.6,0.65, 0.85,0.89);
leg3->SetBorderSize(0);
leg3->AddEntry(hh1, "1 MIP", "l");
leg3->AddEntry(hh2, "2 MIP", "l");
leg3->AddEntry(hh3, "3 MIP", "l");

auto f2 = new TF1("R_L","R_Light",0.1,2,1);
f2->SetParameter(0,1);
f2->SetLineColor(1);
f2->DrawCopy("same");
f2->SetParameter(0,2);
f2->SetLineColor(2);
f2->DrawCopy("same");
f2->SetParameter(0,3);
f2->SetLineColor(4);
f2->DrawCopy("same");
    leg3->Draw();

c1->SaveAs("plot/RL_Efield.pdf");
c1->SaveAs("plot/RL_Efield.C");
}

double R_Charge(double *MIP, double *E){

double dEdx = MIP[0]*2.1;
double A_3t = 0.8;
double k_3t = 0.0486;
double rho=1.38;
double ips = E[0]*rho;
double R=A_3t/(1+k_3t/ips*dEdx);

return R;
}

double R_Light(double *E, double *MIP){
double alpha=0.21;
double beta=1./(1+0.21);

double R_L = 1-beta*R_Charge(MIP,E);

return R_L;	
}
