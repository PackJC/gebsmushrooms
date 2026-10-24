// What the player sees while Geb's Mushroom Field Guide is unfolded on a server with the 2D map: the guide as a page on
// the screen, the way vanilla's map screen shows the map (the cursor, the world shut out, the same keys to close it).
// Vanilla's ActionUnfoldMap opens MENU_MAP; geb_MushroomGuideMission puts this menu in the map screen's place while the
// guide is in the hands. On servers with the 3D map no menu opens and the guide is read in the hands, as vanilla's map
// is. The printed part of the sheet fills most of the screen with the legend's badges and habitats beside it. The mouse
// wheel zooms the sheet round the cursor and dragging with the left button moves it, as on the map. Built in script
// from the item's own textures, so there's no layout file or extra image to pack.
class geb_MushroomGuideMenu extends UIScriptedMenu
{
	protected static const string SHEET = "gebsmushrooms/data/guide/mushroomguide_sheet_co.paa";
	protected static const string LEGEND = "gebsmushrooms/data/guide/mushroomguide_legend_co.paa";
	// the printed parts of those textures (tools/guide/guidekit.py: SHEET_SIZE, SHEET_USED_H, LEGEND_USED_W and the
	// bottom of the habitats panel in LEGEND_PANELS)
	protected static const float SHEET_TEX = 2048;
	protected static const float SHEET_USED_H = 1861;
	protected static const float LEGEND_TEX_W = 512;
	protected static const float LEGEND_TEX_H = 2048;
	protected static const float LEGEND_USED_W = 454;
	protected static const float LEGEND_USED_H = 1352;
	protected static const float ZOOM_MAX = 4;

	protected bool m_IsOpening;
	protected ImageWidget m_Sheet;
	protected float m_ViewX;			// the sheet's window on the screen, pixels
	protected float m_ViewY;
	protected float m_ViewW;
	protected float m_ViewH;
	protected float m_Zoom = 1;
	protected float m_PanX;				// the sheet's top left inside its window
	protected float m_PanY;
	protected bool m_Dragging;
	protected int m_DragX;
	protected int m_DragY;

	override Widget Init()
	{
		int sw;
		int sh;
		GetScreenSize(sw, sh);
		WorkspaceWidget ws = g_Game.GetWorkspace();

		// the whole screen, dark, as the map screen covers the world
		layoutRoot = ws.CreateWidget(FrameWidgetTypeID, 0, 0, sw, sh, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE, ARGB(255, 255, 255, 255), 0);
		ws.CreateWidget(ImageWidgetTypeID, 0, 0, sw, sh, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.BLEND, ARGB(242, 18, 16, 12), 0, layoutRoot);

		// the sheet beside the legend, as tall as the screen allows, the pair centred
		float margin = sh * 0.04;
		float h = sh - 2 * margin;
		float gap = sh * 0.02;
		float sheetW = h * SHEET_TEX / SHEET_USED_H;
		float legendW = h * LEGEND_USED_W / LEGEND_USED_H;
		float fit = (sw - 2 * margin) / (sheetW + gap + legendW);
		if (fit < 1)
		{
			h = h * fit;
			sheetW = sheetW * fit;
			legendW = legendW * fit;
			gap = gap * fit;
		}

		m_ViewW = sheetW;
		m_ViewH = h;
		m_ViewX = (sw - sheetW - gap - legendW) / 2;
		m_ViewY = (sh - h) / 2;

		// each picture sits in a frame that clips it to the printed part (and, for the sheet, to its window when zoomed)
		Widget view = ws.CreateWidget(FrameWidgetTypeID, m_ViewX, m_ViewY, m_ViewW, m_ViewH, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.CLIPCHILDREN, ARGB(255, 255, 255, 255), 1, layoutRoot);
		m_Sheet = ImageWidget.Cast(ws.CreateWidget(ImageWidgetTypeID, 0, 0, m_ViewW, m_ViewW, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.STRETCH, ARGB(255, 255, 255, 255), 0, view));
		if (m_Sheet)
			m_Sheet.LoadImageFile(0, SHEET);

		float legendX = m_ViewX + sheetW + gap;
		Widget legendView = ws.CreateWidget(FrameWidgetTypeID, legendX, m_ViewY, legendW, h, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.CLIPCHILDREN, ARGB(255, 255, 255, 255), 1, layoutRoot);
		float legendFullW = legendW * LEGEND_TEX_W / LEGEND_USED_W;
		float legendFullH = h * LEGEND_TEX_H / LEGEND_USED_H;
		ImageWidget legend = ImageWidget.Cast(ws.CreateWidget(ImageWidgetTypeID, 0, 0, legendFullW, legendFullH, WidgetFlags.VISIBLE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.STRETCH, ARGB(255, 255, 255, 255), 0, legendView));
		if (legend)
			legend.LoadImageFile(0, LEGEND);

		m_IsOpening = true;
		return layoutRoot;
	}

	// the mouse wheel zooms the sheet round the point under the cursor
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		super.OnMouseWheel(w, x, y, wheel);

		int mx;
		int my;
		GetMousePos(mx, my);
		if (!m_Sheet || !InSheet(mx, my))
			return false;

		float zoom = Math.Clamp(m_Zoom * Math.Pow(1.25, wheel), 1, ZOOM_MAX);
		float localX = mx - m_ViewX;
		float localY = my - m_ViewY;
		m_PanX = localX - (localX - m_PanX) * zoom / m_Zoom;
		m_PanY = localY - (localY - m_PanY) * zoom / m_Zoom;
		m_Zoom = zoom;
		PlaceSheet();
		return true;
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);

		// dragging with the left button moves the zoomed sheet
		int mx;
		int my;
		GetMousePos(mx, my);
		bool held = false;
		if (GetMouseState(MouseState.LEFT) & 0x80000000)
			held = true;

		if (!held)
		{
			m_Dragging = false;
		}
		else if (m_Dragging)
		{
			m_PanX = m_PanX + mx - m_DragX;
			m_PanY = m_PanY + my - m_DragY;
			m_DragX = mx;
			m_DragY = my;
			PlaceSheet();
		}
		else if (InSheet(mx, my))
		{
			m_Dragging = true;
			m_DragX = mx;
			m_DragY = my;
		}

		// as MapMenu: ignore the frame the menu opened on, then close on the back key, or on the map key when the
		// server lets players open the map without one
		if (!m_IsOpening)
		{
			bool isClosedWithShortcut = CfgGameplayHandler.GetMapIgnoreMapOwnership() && GetUApi().GetInputByID(UAMapToggle).LocalPress();
			if (GetUApi().GetInputByID(UAUIBack).LocalPress() || isClosedWithShortcut)
			{
				CloseGuide();
			}
		}

		m_IsOpening = false;
	}

	protected bool InSheet(int x, int y)
	{
		return x >= m_ViewX && x <= m_ViewX + m_ViewW && y >= m_ViewY && y <= m_ViewY + m_ViewH;
	}

	// the sheet at its zoom, kept covering its window
	protected void PlaceSheet()
	{
		float size = m_ViewW * m_Zoom;
		float usedH = size * SHEET_USED_H / SHEET_TEX;
		m_PanX = Math.Clamp(m_PanX, m_ViewW - size, 0);
		m_PanY = Math.Clamp(m_PanY, m_ViewH - usedH, 0);
		m_Sheet.SetSize(size, size);
		m_Sheet.SetPos(m_PanX, m_PanY);
	}

	// as MapMenu.CloseMapMenu
	protected void CloseGuide()
	{
		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
		if (player)
			player.SetMapClosingSyncSet(false);		// the map is closing: the server is told once

		if (CfgGameplayHandler.GetMapIgnoreMapOwnership())
		{
			if (!CfgGameplayHandler.GetUse3DMap())
			{
				g_Game.GetMission().RemoveActiveInputExcludes({"map"});
			}
			else
			{
				g_Game.GetMission().RemoveActiveInputExcludes({"loopedactions"});
			}

			g_Game.GetMission().RemoveActiveInputRestriction(EInputRestrictors.MAP);
		}

		Close();
	}
};
