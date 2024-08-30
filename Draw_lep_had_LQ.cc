void Draw_lep_had_LQ(){
TCanvas *c1 = new TCanvas("c1","c1",800,600);
TPad *pad1 = new TPad("pad1","pad1",0,0,1,0.5);
pad1->SetGrid();
pad1->SetTopMargin(0);
pad1->SetBottomMargin(0.2);
//pad1->SetBorderMode();
pad1->Draw();
pad1->cd();

int ndiv = 505;

    TH2D *h_axis = new TH2D("h_re_1","",1,0,1.1,1,0,1);
    h_axis->Draw("");
	h_axis->GetYaxis()->SetNdivisions(ndiv);
    h_axis->GetXaxis()->SetTitle("Calorimeters response");
	h_axis->GetXaxis()->CenterTitle();
    h_axis->GetXaxis()->SetTitleOffset(0.9);
    h_axis->GetXaxis()->SetTitleSize(0.1);
    h_axis->GetXaxis()->SetLabelSize(0.08);
    h_axis->GetYaxis()->SetLabelSize(0.08);
//    h_axis->GetXaxis()->SetTitleSize(0.06);
//    h_axis->GetYaxis()->SetTitleSize(0.06);
	
    gStyle->SetOptStat(0);


TChain *t1 = new TChain("Sim");
t1->Add("/data2/users/xning/output/thre_track_leha_edep_nue_*GeV_1kevts.root");
    TH1D* h_Q_lep = new TH1D("h_Q_lep","",100,0,1.1);
    TH1D* h_Q_had = new TH1D("h_Q_had","",100,0,1.1);
    TH1D* h_L_lep = new TH1D("h_L_lep","",100,0,1.1);
    TH1D* h_L_had = new TH1D("h_L_had","",100,0,1.1);

    h_Q_lep->SetLineColor(4);
    h_Q_had->SetLineColor(2);
    h_L_lep->SetLineColor(4);
    h_L_had->SetLineColor(2);
	t1->Draw("(Q_depoList_thre[0]+Q_depoList_thre[6]+Q_depoList_thre[4])/(E_availList[0]+E_availList[6]+E_availList[4])*0.83>>h_Q_lep","","same hist");
    t1->Draw("(Q_depoList_thre[1]+Q_depoList_thre[2]+Q_depoList_thre[3]+Q_depoList_thre[5])/            (E_availList[1]+E_availList[2]+E_availList[3]+E_availList[5])*0.83>>h_Q_had","","same hist");
	h_Q_lep->Scale(1./h_Q_lep->Integral());
	h_Q_had->Scale(1./h_Q_had->Integral());
	TLatex text;
	text.SetTextSize(0.1);
	text.DrawLatex(0.1,0.8,"(Charge)");


c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0.5,1,1);
pad2->SetGrid();
pad2->SetBottomMargin(0);
//pad2->SetBorderMode(0);
pad2->Draw();
pad2->cd();

    h_axis->Draw("");

    t1->Draw("(E_depoList_l[0]+E_depoList_l[6]+E_depoList_l[4])/(E_availList[0]+E_availList[6]+         E_availList[4])>>h_L_lep","","same hist");
    t1->Draw("(E_depoList_l[1]+E_depoList_l[2]+E_depoList_l[3]+E_depoList_l[5])/(E_availList[1]+        E_availList[2]+E_availList[3]+E_availList[5])>>h_L_had","","same hist");
	h_L_lep->Scale(1./h_L_lep->Integral());
	h_L_had->Scale(1./h_L_had->Integral());
	text.DrawLatex(0.1,0.8,"(Light)");


	TLegend *leg3 = new TLegend(0.7,0.30, 0.85,0.7);
    leg3->SetBorderSize(0);
    leg3->AddEntry(h_Q_lep, "e", "l");
    leg3->AddEntry(h_Q_had, "h", "l");
    leg3->Draw();

c1->cd();
TPad *pad3 = new TPad("pad3","pad3",0,0,0.1,1);
pad3->Draw();
pad3->cd();
auto *tt = new TText(0.8,0.4,"Probability");
tt->SetTextFont(133);
tt->SetTextSize(30);
tt->SetTextAngle(90);
tt->Draw();

	c1->SaveAs("plot/lep_had_LQ.pdf");
	c1->SaveAs("plot/lep_had_LQ.C");

TFile *f1 = new TFile("plot/lep_had_LQ.root","recreate");
c1->Write();
h_L_lep->Write();
h_L_had->Write();
h_Q_lep->Write();
h_Q_had->Write();
f1->Close();


}
