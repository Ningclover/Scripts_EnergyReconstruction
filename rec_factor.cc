void rec_factor(){
TCanvas *c1 = new TCanvas("c1","c1",800,600);
gPad->SetGrid();

auto f1 = new TF1("R_C","R_Charge",0.1,10,1);
f1->SetParameter(0,0.5);
f1->Draw();
f1->GetYaxis()->SetRangeUser(0,0.9);
f1->GetYaxis()->SetTitle("Recombination Factor");
f1->GetXaxis()->SetTitle("dE/dx [2.1MeV/cm]");
f1->GetYaxis()->CenterTitle();
f1->GetXaxis()->CenterTitle();
//f1->GetXaxis()->SetTitle("Number of MIP [2.1MeV/cm]");
//f1->GetXaxis()->SetTitle("#frac{dE/dx}{2.1MeV/cm}");
auto f2 = new TF1("R_L","R_Light",0.1,10,1);
f2->SetParameter(0,0.5);
f2->Draw("same");
f2->SetLineColor(1);
    TLegend *leg3 = new TLegend(0.3,0.25, 0.5,0.4);
    leg3->SetBorderSize(0);
    leg3->AddEntry(f1, "R_{C}", "l");
    leg3->AddEntry(f2, "R_{L}", "l");
    leg3->Draw();

c1->SaveAs("plot/RCRL.pdf");
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

double R_Light(double *MIP, double *E){
double alpha=0.21;
double beta=1./(1+0.21);

double R_L = 1-beta*R_Charge(MIP,E);

return R_L;	
}
