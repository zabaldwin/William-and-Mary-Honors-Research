using namespace RooFit;

void ex_RooFit(){


//Build Gaussian PDF
RooRealVar x("x","x", -10, 10);
RooRealVar mean("mean","mean of gaussian", 0, -10, 10);
RooRealVar sigma("sigma","width of gaussian", 3);

RooGaussian gauss("gauss","gaussian PDF", x, mean, sigma);

//Plot
RooPlot* xframe =x.frame();
gauss.plotOn(xframe);
xframe->Draw();







return;}
