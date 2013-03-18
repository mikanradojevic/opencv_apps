#include "graph.h"


void c_histogram_layar::Plot(wxDC & dc, mpWindow & w)
{
	if (m_visible)
	{
		dc.SetPen(m_pen); 

		wxCoord start_px = m_drawOutsideMargins? 0 : w.GetMarginLeft();
		wxCoord end_px = m_drawOutsideMargins? w.GetScrX() : w.GetScrX() - w.GetMarginRight();
		wxCoord min_y_px = m_drawOutsideMargins ? 0 : w.GetMarginTop();
		wxCoord max_y_px = m_drawOutsideMargins ? w.GetScrY() : w.GetScrY() - w.GetMarginBottom();

		wxCoord y0 = w.y2p(0); 
		wxCoord iy = 0;
		
		for (wxCoord i = start_px; i < end_px; ++i) 
		{
			iy = w.y2p(GetY(w.p2x(i)));
			
			if (m_drawOutsideMargins || (iy >= min_y_px) && (iy <= max_y_px))
				dc.DrawLine(i, y0, i, iy);
		}

		if (!m_name.IsEmpty() && m_showName)
		{
			dc.SetFont(m_font);

			wxCoord tx, ty;
			dc.GetTextExtent(m_name, &tx, &ty);

			/*if ((m_flags & mpALIGNMASK) == mpALIGN_RIGHT)
				tx = (w.GetScrX()>>1) - tx - 8;
			else if ((m_flags & mpALIGNMASK) == mpALIGN_CENTER)
				tx = -tx/2;
			else
				tx = -(w.GetScrX()>>1) + 8;
			*/
			if ((m_flags & mpALIGNMASK) == mpALIGN_RIGHT) 
				tx = (w.GetScrX() - tx) - w.GetMarginRight() - 8; 
			else if ((m_flags & mpALIGNMASK) == mpALIGN_CENTER) 
				tx = ((w.GetScrX() - w.GetMarginRight() - w.GetMarginLeft() - tx) / 2) + w.GetMarginLeft(); 
			else 
				tx = w.GetMarginLeft() + 8;
			dc.DrawText( m_name, tx, w.y2p(GetY(w.p2x(tx))) ); // (wxCoord) ((w.GetPosY() - GetY( (double)tx / w.GetScaleX() + w.GetPosX())) * w.GetScaleY()) );
		}

	} 
}

//////////////////////////////////////////////////////////////////////////

void c_mtf_layer::Plot(wxDC & dc, mpWindow & w)
{
    if (m_visible)
    {
        dc.SetPen(m_pen); 

        wxCoord start_px = m_drawOutsideMargins? 0 : w.GetMarginLeft();
        wxCoord end_px = m_drawOutsideMargins? w.GetScrX() : w.GetScrX() - w.GetMarginRight();
        wxCoord min_y_px = m_drawOutsideMargins ? 0 : w.GetMarginTop();
        wxCoord max_y_px = m_drawOutsideMargins ? w.GetScrY() : w.GetScrY() - w.GetMarginBottom();

        wxCoord y0 = w.y2p(0); 
        wxCoord ix = 0;
        wxCoord iy = w.y2p(GetY(w.p2x(0)));
        
        for (wxCoord i = start_px + 1; i < end_px; ++i) 
        {
            wxCoord y = w.y2p(GetY(w.p2x(i)));
            if (m_drawOutsideMargins || (iy >= min_y_px) && (iy <= max_y_px))
                dc.DrawLine(i-1, iy, i, y);
            
            iy = y; 
        }

        if (!m_name.IsEmpty() && m_showName)
        {
            dc.SetFont(m_font);

            wxCoord tx, ty;
            dc.GetTextExtent(m_name, &tx, &ty);
			
            if ((m_flags & mpALIGNMASK) == mpALIGN_RIGHT) 
                tx = (w.GetScrX() - tx) - w.GetMarginRight() - 8; 
            else if ((m_flags & mpALIGNMASK) == mpALIGN_CENTER) 
                tx = ((w.GetScrX() - w.GetMarginRight() - w.GetMarginLeft() - tx) / 2) + w.GetMarginLeft(); 
            else 
                tx = w.GetMarginLeft() + 8;
            dc.DrawText( m_name, tx, w.y2p(GetY(w.p2x(tx))) ); // (wxCoord) ((w.GetPosY() - GetY( (double)tx / w.GetScaleX() + w.GetPosX())) * w.GetScaleY()) );
        }
    }
}