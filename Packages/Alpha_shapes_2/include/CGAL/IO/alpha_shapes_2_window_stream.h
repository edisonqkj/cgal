// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.0-I-20 $
// release_date  : $CGAL_Date: 1999/06/02 $
//
// file          : include/CGAL/IO/alpha_shapes_2_window_stream.h
// package       : Alpha_shapes_2(1.0)
// source        : $RCSfile$
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Tran Kai Frank DA <Frank.Da@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
//
// ======================================================================


#ifdef CGAL_ALPHA_WINDOW_STREAM

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template < class Gt, class Tds >
Window_stream&
Alpha_shape_2<Gt,Tds>::op_window(Window_stream& W) const
{

  typedef typename Alpha_shape_2<Gt,Tds>::Interval_vertex_map Interval_vertex_map;
  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  typedef  typename Alpha_shape_2<Gt,Tds>::Interval_edge_map Interval_edge_map;
  typename Interval_edge_map::const_iterator edge_alpha_it;

  const typename Alpha_shape_2<Gt,Tds>::Interval3* pInterval;

  if (get_mode() == Alpha_shape_2<Gt,Tds>::REGULARIZED) 
    {

      // it is much faster looking at the sorted intervals 
      // than looking at all sorted faces
      // alpha must be larger than the mid boundary
      // and alpha is smaller than the upper boundary
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;

	  CGAL_triangulation_assertion(pInterval->second != INFINITY);
	  // since this happens only for convex hull of dimension 1
	  // thus singular

	  if(pInterval->second < get_alpha() &&
	     (pInterval->third >= get_alpha()
	      || pInterval->third == INFINITY)) 
	    {
	      // alpha must be larger than the mid boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary
	    
	      CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
						       (*edge_alpha_it).second.second) ==
					    Alpha_shape_2<Gt,Tds>::REGULAR));
	      // if we used Edelsbrunner and Muecke's definition
	      // regular means incident to a higher-dimensional face
	      // thus we would write to many vertices
	      W << segment((*edge_alpha_it).second.first,
			     (*edge_alpha_it).second.second);
	    }
	}
    }
  else 
    { // get_mode() == GENERAL

      // draw the edges
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
	
	  pInterval = &(*edge_alpha_it).first;

	  if (pInterval->first == UNDEFINED) 
	    {
	    
	      CGAL_triangulation_assertion(pInterval->second != INFINITY);
	      // since this happens only for convex hull of dimension 1
	      // thus singular

	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
		
		  CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
							   (*edge_alpha_it).second.second) ==
						Alpha_shape_2<Gt,Tds>::REGULAR));
		  W << segment((*edge_alpha_it).second.first,
				 (*edge_alpha_it).second.second);
		}
	    }
	  else 
	    {
	   

	      if(pInterval->third >= get_alpha()
		 || pInterval->third == INFINITY) 
		{
		  // if alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
		
		  CGAL_triangulation_assertion(((classify((*edge_alpha_it).second.first,
							    (*edge_alpha_it).second.second) ==
						 Alpha_shape_2<Gt,Tds>::REGULAR) || 
						(classify((*edge_alpha_it).second.first,
							    (*edge_alpha_it).second.second) ==
						 Alpha_shape_2<Gt,Tds>::SINGULAR)));
		  W << segment((*edge_alpha_it).second.first,
				 (*edge_alpha_it).second.second);
		}
	    }

	}
    }

  // draw the vertices
  typename Alpha_shape_2<Gt,Tds>::Vertex_handle v;
  for (vertex_alpha_it = _interval_vertex_map.begin(); 
       vertex_alpha_it != _interval_vertex_map.end();
       ++vertex_alpha_it) 
    {
	
      v = (*vertex_alpha_it).second;
      W << v->point();
    }
  return W;
}

//-------------------------------------------------------------------

template < class Gt, class Tds >
Window_stream& 
operator<<(Window_stream& W, const Alpha_shape_2<Gt,Tds>& As) 
{
  return As.op_window(W);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif//CGAL_ALPHA_WINDOW_STREAM

//-----------------------------------------------------------------------

#ifdef CGAL_WEIGHTED_ALPHA_WINDOW_STREAM

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template < class Gt, class Tds >
Window_stream&
Weighted_alpha_shape_2<Gt,Tds>::op_window(Window_stream& W) const
{

  typedef typename Weighted_alpha_shape_2<Gt,Tds>::Interval_vertex_map Interval_vertex_map;
  typename Interval_vertex_map::const_iterator vertex_alpha_it;

  typedef  typename Weighted_alpha_shape_2<Gt,Tds>::Interval_edge_map Interval_edge_map;
  typename Interval_edge_map::const_iterator edge_alpha_it;

  const typename Weighted_alpha_shape_2<Gt,Tds>::Interval3* pInterval;

  if (get_mode() == Weighted_alpha_shape_2<Gt,Tds>::REGULARIZED) 
    {
      // it is much faster looking at the sorted intervals 
      // than looking at all sorted faces
      // alpha must be larger than the mid boundary
      // and alpha is smaller than the upper boundary
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{
      
	  pInterval = &(*edge_alpha_it).first;

	  CGAL_triangulation_assertion(pInterval->second != INFINITY);
	  // since this happens only for convex hull of dimension 1
	  // thus singular
      
	  if(pInterval->second < get_alpha() &&
	     (pInterval->third >= get_alpha()
	      || pInterval->third == INFINITY)) 
	    {
	      // alpha must be larger than the mid boundary
	      // and alpha is smaller than the upper boundary
	      // which might be infinity 
	      // visualize the boundary
	
	      CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
						       (*edge_alpha_it).second.second) ==
					    Weighted_alpha_shape_2<Gt,Tds>::REGULAR));
	      // if we used Edelsbrunner and Muecke's definition
	      // regular means incident to a higher-dimensional face
	      // thus we would write to many vertices
	      W << segment((*edge_alpha_it).second.first,
			     (*edge_alpha_it).second.second);
	    }
	}
    }
  else
    {  // get_mode() == GENERAL
    
      // draw the edges
      for (edge_alpha_it = _interval_edge_map.begin(); 
	   edge_alpha_it != _interval_edge_map.end() &&
	     (*edge_alpha_it).first.first < get_alpha();
	   ++edge_alpha_it) 
	{

	  pInterval = &(*edge_alpha_it).first;
      
	  if (pInterval->first == UNDEFINED) 
	    {
	
	      CGAL_triangulation_assertion(pInterval->second != INFINITY);
	      // since this happens only for convex hull of dimension 1
	      // thus singular
	
	      if(pInterval->second < get_alpha() &&
		 (pInterval->third >= get_alpha()
		  || pInterval->third == INFINITY)) 
		{
		  // alpha must be larger than the mid boundary
		  // and alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
	  
		  CGAL_triangulation_assertion((classify((*edge_alpha_it).second.first,
							   (*edge_alpha_it).second.second) ==
						Weighted_alpha_shape_2<Gt,Tds>::REGULAR));
		  W << segment((*edge_alpha_it).second.first,
				 (*edge_alpha_it).second.second);
		}
	    }
	  else
	    {
	
	      if(pInterval->third >= get_alpha()
		 || pInterval->third == INFINITY) 
		{
		  // if alpha is smaller than the upper boundary
		  // which might be infinity 
		  // visualize the boundary
	  
		  CGAL_triangulation_assertion(((classify((*edge_alpha_it).second.first,
							    (*edge_alpha_it).second.second) ==
						 Weighted_alpha_shape_2<Gt,Tds>::REGULAR) || 
						(classify((*edge_alpha_it).second.first,
							    (*edge_alpha_it).second.second) ==
						 Weighted_alpha_shape_2<Gt,Tds>::SINGULAR)));
		  W << segment((*edge_alpha_it).second.first,
				 (*edge_alpha_it).second.second);
		}
	    }
      
	}
    }
  
  // draw the vertices
  
  typename Weighted_alpha_shape_2<Gt,Tds>::Vertex_handle v;
  for (vertex_alpha_it = _interval_vertex_map.begin(); 
       vertex_alpha_it != _interval_vertex_map.end();
       ++vertex_alpha_it) 
    {
    
      v = (*vertex_alpha_it).second;
      W << (v->point()).point();
    }
  
  return W;
}

//-------------------------------------------------------------------

template < class Gt, class Tds >
Window_stream& 
operator<<(Window_stream& W, const Weighted_alpha_shape_2<Gt,Tds>& A) 
{
  return A.op_window(W);
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //CGAL_WEIGHTED_ALPHA_WINDOW_STREAM
