#ifdef __CLING__
#pragma cling optimize(0)
#endif
void RL_Efield()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Sep  4 14:51:29 2024) by ROOT version 6.28/06
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-0.4444444,0.1702703,2.333333,0.9810811);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetRightMargin(0.12);
   c1->SetBottomMargin(0.16);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH2D *h1__1 = new TH2D("h1__1","h1",1,0,2,1,0.3,0.9);
   h1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->SetLineWidth(2);
   h1__1->SetMarkerStyle(20);
   h1__1->SetMarkerSize(0.6);
   h1__1->GetXaxis()->SetTitle("Drift E field [kV/cm]");
   h1__1->GetXaxis()->CenterTitle(true);
   h1__1->GetXaxis()->SetLabelFont(132);
   h1__1->GetXaxis()->SetLabelSize(0.06);
   h1__1->GetXaxis()->SetTitleSize(0.06);
   h1__1->GetXaxis()->SetTitleOffset(1.1);
   h1__1->GetXaxis()->SetTitleFont(132);
   h1__1->GetYaxis()->SetTitle("R_{L}");
   h1__1->GetYaxis()->CenterTitle(true);
   h1__1->GetYaxis()->SetLabelFont(132);
   h1__1->GetYaxis()->SetLabelSize(0.06);
   h1__1->GetYaxis()->SetTitleSize(0.06);
   h1__1->GetYaxis()->SetTitleOffset(1.2);
   h1__1->GetYaxis()->SetTitleFont(132);
   h1__1->GetZaxis()->SetLabelFont(132);
   h1__1->GetZaxis()->SetLabelSize(0.06);
   h1__1->GetZaxis()->SetTitleSize(0.06);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(132);
   h1__1->Draw("axis");
   
   TF1 *R_L1 = new TF1("R_L","",0.1,2, TF1::EAddToList::kDefault);
   R_L1->SetFillColor(19);
   R_L1->SetFillStyle(0);
   R_L1->SetMarkerStyle(20);
   R_L1->SetMarkerSize(0.6);
   R_L1->SetLineWidth(2);
   R_L1->GetXaxis()->SetLabelFont(132);
   R_L1->GetXaxis()->SetLabelSize(0.06);
   R_L1->GetXaxis()->SetTitleSize(0.06);
   R_L1->GetXaxis()->SetTitleOffset(1.1);
   R_L1->GetXaxis()->SetTitleFont(132);
   R_L1->GetYaxis()->SetLabelFont(132);
   R_L1->GetYaxis()->SetLabelSize(0.06);
   R_L1->GetYaxis()->SetTitleSize(0.06);
   R_L1->GetYaxis()->SetTitleOffset(1.2);
   R_L1->GetYaxis()->SetTitleFont(132);
   R_L1->SetParameter(0,1);
   R_L1->SetParError(0,0);
   R_L1->SetParLimits(0,0,0);
   R_L1->Draw("same");
   
   TF1 *R_L2 = new TF1("R_L","",0.1,2, TF1::EAddToList::kDefault);
   R_L2->SetFillColor(19);
   R_L2->SetFillStyle(0);
   R_L2->SetMarkerStyle(20);
   R_L2->SetMarkerSize(0.6);
   R_L2->SetLineColor(2);
   R_L2->SetLineWidth(2);
   R_L2->GetXaxis()->SetLabelFont(132);
   R_L2->GetXaxis()->SetLabelSize(0.06);
   R_L2->GetXaxis()->SetTitleSize(0.06);
   R_L2->GetXaxis()->SetTitleOffset(1.1);
   R_L2->GetXaxis()->SetTitleFont(132);
   R_L2->GetYaxis()->SetLabelFont(132);
   R_L2->GetYaxis()->SetLabelSize(0.06);
   R_L2->GetYaxis()->SetTitleSize(0.06);
   R_L2->GetYaxis()->SetTitleOffset(1.2);
   R_L2->GetYaxis()->SetTitleFont(132);
   R_L2->SetParameter(0,2);
   R_L2->SetParError(0,0);
   R_L2->SetParLimits(0,0,0);
   R_L2->Draw("same");
   
   TF1 *R_L3 = new TF1("R_L","",0.1,2, TF1::EAddToList::kDefault);
   R_L3->SetFillColor(19);
   R_L3->SetFillStyle(0);
   R_L3->SetMarkerStyle(20);
   R_L3->SetMarkerSize(0.6);
   R_L3->SetLineColor(4);
   R_L3->SetLineWidth(2);
   R_L3->GetXaxis()->SetLabelFont(132);
   R_L3->GetXaxis()->SetLabelSize(0.06);
   R_L3->GetXaxis()->SetTitleSize(0.06);
   R_L3->GetXaxis()->SetTitleOffset(1.1);
   R_L3->GetXaxis()->SetTitleFont(132);
   R_L3->GetYaxis()->SetLabelFont(132);
   R_L3->GetYaxis()->SetLabelSize(0.06);
   R_L3->GetYaxis()->SetTitleSize(0.06);
   R_L3->GetYaxis()->SetTitleOffset(1.2);
   R_L3->GetYaxis()->SetTitleFont(132);
   R_L3->SetParameter(0,3);
   R_L3->SetParError(0,0);
   R_L3->SetParLimits(0,0,0);
   R_L3->Draw("same");
   
   TLegend *leg = new TLegend(0.6,0.65,0.85,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(133);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hh1","1 MIP","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("hh2","2 MIP","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("hh3","3 MIP","l");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
