// File:	GccAna_CircLin2dBisec.cxx
// Created:	Fri Oct 11 08:19:14 1991
// Author:	Remi GILET
//		<reg@topsn3>

//=========================================================================
//   CREATION of the BISSECTICE between a CIRCLE and a STRAIGHT LINE.             +
//=========================================================================

#include <GccAna_CircLin2dBisec.ixx>

#include <gp_XY.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Ax2d.hxx>
#include <GccInt_BParab.hxx>
#include <GccInt_BLine.hxx>
#include <Standard_OutOfRange.hxx>
#include <StdFail_NotDone.hxx>
#include <gp.hxx>

//=========================================================================

GccAna_CircLin2dBisec::
   GccAna_CircLin2dBisec (const gp_Circ2d& Circle ,
		          const gp_Lin2d&  Line   ):

   circle(Circle),
   line(Line)
{

//=========================================================================
//  Initialization of fields :                                           +
//            - circle                                       +
//            - line     (straight line.)                                     +
//            - NbrSol   (number of solution.)                            +
//            - WellDone (Booleen showing success or failure of algorithm). +
//=========================================================================

   NbrSol = 2;
   WellDone = Standard_True;
 }

//=========================================================================
//  Processing.                                                           +
//  Return coordinates of origins of the straight line (xloc,yloc) and the  +
//  circle (xcencir, ycencir).                                         +
//  Also return the coordinates of the direction of the straight line (xdir,   +
//  ydir) and the radius of circle R1.                                       +
//  Check at which side of the straight line is found the center of the circle    +
//  to orientate the parabola (sign).                                    +
//  Create axis of each parabola (axeparab1, axeparb2), then     +
//  two parabolas (biscirlin1, biscirlin1).                          +
//=========================================================================

Handle(GccInt_Bisec) GccAna_CircLin2dBisec::
   ThisSolution (const Standard_Integer Index) const 
{
  
  if (!WellDone) StdFail_NotDone::Raise();
  
  if ((Index <=0) || (Index > NbrSol)) Standard_OutOfRange::Raise();
  
  Handle(GccInt_Bisec) bissol;
  Standard_Real xdir = line.Direction().X();
  Standard_Real ydir = line.Direction().Y();
  Standard_Real xloc = line.Location().X();
  Standard_Real yloc = line.Location().Y();
  Standard_Real xcencir = circle.Location().X();
  Standard_Real ycencir = circle.Location().Y();
  Standard_Real R1 = circle.Radius();
  Standard_Real dist = line.Distance(circle.Location());
  if ((Abs(line.Distance(circle.Location())-circle.Radius()) 
       <= gp::Resolution()) && (Index == 1)) {
    gp_Lin2d biscirlin1(circle.Location(),gp_Dir2d(-ydir,xdir));
    bissol = new GccInt_BLine(biscirlin1);
    //       ==========================================================
  }
  else {
    Standard_Integer signe;
    if ((-ydir*(xcencir-xloc)+xdir*(ycencir-yloc)) > 0.0) {
      signe = 1;
    }
    else {
      signe = -1;
    }
    gp_Ax2d axeparab1;
//    gp_Ax2d axeparab2;
    gp_Parab2d biscirlin;
    if (dist != R1) {
      if (Index == 1) {
	axeparab1=gp_Ax2d(gp_Pnt2d(gp_XY(xcencir+signe*ydir*(dist+R1)/2,
					 ycencir-signe*xdir*(dist+R1)/2.)),
			  gp_Dir2d(-signe*ydir,signe*xdir));
	biscirlin = gp_Parab2d(axeparab1,(dist+R1)/2.0);
      }
      else {
	if (dist < R1) {
	  axeparab1=gp_Ax2d(gp_Pnt2d(gp_XY(xcencir+signe*ydir*(dist-R1)/2,
					   ycencir-signe*xdir*(dist-R1)/2.)),
			    gp_Dir2d(signe*ydir,-signe*xdir));
	}
	else {
	  axeparab1=gp_Ax2d(gp_Pnt2d(gp_XY(xcencir+signe*ydir*(dist-R1)/2,
					   ycencir-signe*xdir*(dist-R1)/2.)),
			    gp_Dir2d(-signe*ydir,signe*xdir));
	}
	biscirlin = gp_Parab2d(axeparab1,Abs(dist-R1)/2.0);
      }
      bissol = new GccInt_BParab(biscirlin);
      //         ==========================================================
    }
    else {
      axeparab1 = gp_Ax2d(gp_Pnt2d(gp_XY(xcencir+signe*ydir*(dist+R1)/2.,
					 ycencir-signe*xdir*(dist+R1)/2.)),
			  gp_Dir2d(signe*(-ydir),signe*xdir));
      biscirlin = gp_Parab2d(axeparab1,R1);
      bissol = new GccInt_BParab(biscirlin);
      //         ==========================================================
    }
  }

  return bissol;
}

//=========================================================================

Standard_Boolean GccAna_CircLin2dBisec::
   IsDone () const { return WellDone; }

Standard_Integer GccAna_CircLin2dBisec::
   NbSolutions () const { return NbrSol; }


