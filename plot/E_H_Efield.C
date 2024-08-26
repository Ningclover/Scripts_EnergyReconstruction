#ifdef __CLING__
#pragma cling optimize(0)
#endif
void E_H_Efield()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Aug 26 13:02:27 2024) by ROOT version 6.28/06
   TCanvas *c1 = new TCanvas("c1", "c1",56,65,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-0.4444889,0.6702703,2.333567,1.481081);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetRightMargin(0.12);
   c1->SetBottomMargin(0.16);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[7] = { 0.1, 0.3, 0.5, 0.7, 1, 1.5, 2.5 };
   Double_t Graph0_fy1[7] = { 1.087899, 1.006058, 1.010614, 1.021278, 1.034681, 1.042462, 1.085138 };
   TGraph *graph = new TGraph(7,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetLineColor(2);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.6);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","Graph",100,0,2.74);
   Graph_Graph01->SetMinimum(0.8);
   Graph_Graph01->SetMaximum(1.4);
   Graph_Graph01->SetDirectory(nullptr);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->SetLineWidth(2);
   Graph_Graph01->SetMarkerStyle(20);
   Graph_Graph01->SetMarkerSize(0.6);
   Graph_Graph01->GetXaxis()->SetTitle("E field[kV/cm]");
   Graph_Graph01->GetXaxis()->SetRange(1,73);
   Graph_Graph01->GetXaxis()->SetLabelFont(132);
   Graph_Graph01->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph01->GetXaxis()->SetTitleFont(132);
   Graph_Graph01->GetYaxis()->SetTitle("e/h");
   Graph_Graph01->GetYaxis()->SetLabelFont(132);
   Graph_Graph01->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph01->GetYaxis()->SetTitleFont(132);
   Graph_Graph01->GetZaxis()->SetLabelFont(132);
   Graph_Graph01->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph01->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(132);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("al ");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
