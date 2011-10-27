// File:	GC_MakeTrimmedCylinder.cxx
// Created:	Fri Oct  2 16:38:49 1992
// Author:	Remi GILET
//		<reg@topsn3>

#include <GC_MakeTrimmedCylinder.ixx>
#include <GC_MakeCylindricalSurface.hxx>
#include <StdFail_NotDone.hxx>
#include <Standard_NotImplemented.hxx>

//=========================================================================
//   Creation of a cylinder limited by three points <P1>, <P2> and <P3>.         +
//   the height og the resulting cylinder is the distance from <P1> to <P2>.     +
//   The radius is the distance from <P3> to axis <P1P2>.                 +
//=========================================================================

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Pnt& P1 ,
						 const gp_Pnt& P2 ,
						 const gp_Pnt& P3 ) 
{
  GC_MakeCylindricalSurface Cyl(P1,P2,P3);
  TheError = Cyl.Status();
  if (TheError == gce_Done) {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(),0.,2.*PI,0.,
				  P2.Distance(P1),Standard_True,Standard_True);
  }
}

//=========================================================================
//   Creation of a cylinder limited by a circle and height.          +
//=========================================================================

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Circ&      Circ   ,
						 const Standard_Real Height ) {
  GC_MakeCylindricalSurface Cyl(Circ);
  TheError = Cyl.Status();
  if (TheError == gce_Done) {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(),0.,2.*PI,0.,
					   Height,Standard_True,Standard_True);
  }
}
     
//=========================================================================
//=========================================================================

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Ax1&       A1     ,
						 const Standard_Real Radius ,
						 const Standard_Real Height ) {
  GC_MakeCylindricalSurface Cyl(A1,Radius);
  TheError = Cyl.Status();
  if (TheError == gce_Done) {
    TheCyl = new Geom_RectangularTrimmedSurface(Cyl.Value(),0.,2.*PI,0.,
					Height,Standard_True,Standard_True);
  }
}

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Cylinder& , // Cyl,
						 const gp_Pnt&      , // P,
						 const Standard_Real )//Height)
{
  Standard_NotImplemented::Raise("GC_MakeTrimmedCylinder");
}

GC_MakeTrimmedCylinder::GC_MakeTrimmedCylinder(const gp_Cylinder& , // Cyl,
						 const gp_Pnt&      , // P1,
						 const gp_Pnt&      ) // P2)
{
  Standard_NotImplemented::Raise("GC_MakeTrimmedCylinder");
}

const Handle(Geom_RectangularTrimmedSurface)& GC_MakeTrimmedCylinder::
       Value() const
{ 
  StdFail_NotDone_Raise_if(!TheError == gce_Done,"");
  return TheCyl;
}

const Handle(Geom_RectangularTrimmedSurface)& GC_MakeTrimmedCylinder::
       Operator() const 
{
  return Value();
}

GC_MakeTrimmedCylinder::
  operator Handle(Geom_RectangularTrimmedSurface) () const
{
  return Value();
}

