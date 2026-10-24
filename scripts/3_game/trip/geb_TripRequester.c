// How far the trip's waves may bend the view (a fraction of it): the wet-lens pass's ceiling, raised from vanilla's
// 0.02 by the modded PPEWetDistort at the end of this file
const float GEB_TRIP_WAVE_MAX = 0.08;

// The trip on screen, on the eater's own client (geb_TripClient in scripts/4_world/entities/geb_trip.c drives it each
// frame with the trip's strength). Built only from post-process layers vanilla's own effects use, so it sits beside
// them: the colourisation tint the toxic zones and heavy-metal poisoning shift, the lens distortion and its colour
// fringes heavy-metal poisoning animates, the ghost double image, chromatic aberration, a vignette, a little more
// contrast, the blur fever swells in and out, and the wet-lens waves. Everything scales with the strength; at 0 the
// requester stops and vanilla's values come back.
class PPERequester_GebTrip extends PPERequester_GameplayBase
{
	// our own priority layers (vanilla's on these parameters are 100-800)
	protected static const int L_TINT = 260;
	protected static const int L_LENS = 160;
	protected static const int L_GHOST = 160;
	protected static const int L_FRINGE = 160;
	protected static const int L_VIGNETTE = 260;
	protected static const int L_WAVES = 160;
	protected static const int L_FOCUS = 310;	// just above vanilla's fever blur (PPEGaussFilter.L_0_FEVER)

	protected float m_Time;
	protected ref array<float> m_ChannelWeights = {0, 0, 0, 0};

	override protected void OnStart(Param par = null)
	{
		super.OnStart(par);
		m_Time = 0;
		// the ghost image's noise and size, once (as vanilla's heavy-metal ghosts)
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_NOISE_SCALE_X, false, 0.05, L_GHOST, PPOperators.LOWEST);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_NOISE_SCALE_Y, false, 0.05, L_GHOST, PPOperators.LOWEST);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_GHOST_SCALE_X, false, 1, L_GHOST, PPOperators.LOWEST);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_GHOST_SCALE_Y, false, 1, L_GHOST, PPOperators.LOWEST);
	}

	// strength 0..1 now; delta: seconds since the last frame; fright 0..1: a rare scare at its height (the view goes
	// red and wild for a few seconds, geb_TripClient.Fright), 0 the rest of the time
	void SetTrip(float strength, float delta, float fright = 0)
	{
		float s = Math.Clamp(strength, 0, 1);
		float f = Math.Clamp(fright, 0, 1);
		m_Time += delta * (1 + 2 * f);				// a scare runs everything three times as fast
		float t = m_Time;

		// colours slide slowly round and back: each channel pushed up and down a third of a turn apart (a turn ~25 s)
		float hue = t * 0.25;
		float amp = 0.32 * s;
		float r = 1 + amp * Math.Sin(hue);
		float g = 1 + amp * Math.Sin(hue + 2.094);
		float b = 1 + amp * Math.Sin(hue + 4.189);
		// scaled so the picture keeps its brightness and only its colour moves (a forest is mostly green: pulling
		// green down unscaled darkened the whole view)
		float lum = 0.299 * r + 0.587 * g + 0.114 * b;
		r = Math.Lerp(r / lum, 1.9, f);				// a scare: blood red
		g = Math.Lerp(g / lum, 0.35, f);
		b = Math.Lerp(b / lum, 0.35, f);
		SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, {r, g, b, 0.0}, L_TINT, PPOperators.MULTIPLICATIVE);
		float contrast = 1 + 0.1 * s + 0.15 * f;
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_CONTRAST, false, contrast, L_TINT, PPOperators.HIGHEST);

		// a soft violet closing in at the edges (dark red in a scare)
		float vignette = 0.55 * s + 0.5 * f;
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_VIGNETTE, false, vignette, L_VIGNETTE, PPOperators.ADD);
		float vr = Math.Lerp(0.16 * s, 0.4, f);
		float vg = Math.Lerp(0.02 * s, 0, f);
		float vb = Math.Lerp(0.22 * s, 0.02, f);
		SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_VIGNETTECOLOR, {vr, vg, vb, 0.0}, L_VIGNETTE, PPOperators.ADD);

		// the view breathes: the lens bulges and pinches slowly, its centre wandering, colour fringing with it (in a
		// scare it shudders)
		float breathe = Math.Sin(t * 0.55) * 0.6 + Math.Sin(t * 0.23) * 0.4;
		float wobble = 0.4 * s * Math.Sin(t * 1.9);				// a quicker swim on top, a beat every 3 s or so
		float distort = s * breathe + wobble + 0.35 * f * Math.Sin(t * 6);
		float cx = 0.5 * s * Math.Sin(t * 0.17);
		float cy = 0.35 * s * Math.Cos(t * 0.13);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_DISTORT, false, distort, L_LENS, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CENTERX, false, cx, L_LENS, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CENTERY, false, cy, L_LENS, PPOperators.ADD);
		float lensFringe = 0.35 * s + 0.4 * f;
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CHROM_ABB, true, lensFringe, L_LENS, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CHROM_ABB_SHIFTR, true, 0.1, L_LENS, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CHROM_ABB_SHIFTG, true, 0, L_LENS, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.Distort, PPEDistort.PARAM_CHROM_ABB_SHIFTB, true, 0.75, L_LENS, PPOperators.SET);

		// colour fringes at the edges of the screen, pulsing
		float fringe = 0.0035 * s * (0.7 + 0.3 * Math.Sin(t * 1.3)) + 0.01 * f;
		SetTargetValueFloat(PostProcessEffectType.ChromAber, PPEChromAber.PARAM_POWERX, false, fringe, L_FRINGE, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.ChromAber, PPEChromAber.PARAM_POWERY, false, fringe, L_FRINGE, PPOperators.HIGHEST);

		// a double image circling the picture, never quite lined up with it, showing over more of the view at the peak
		// (in a scare, strong and jerking about)
		for (int i = 0; i < 4; i++)
		{
			m_ChannelWeights[i] = 0.9 * s * (0.35 + 0.65 * (Math.Sin(t * 0.4 + i * Math.PI_HALF) * 0.5 + 0.5)) + 0.4 * f;
		}
		SetTargetValueColor(PostProcessEffectType.Ghost, PPEGhost.PARAM_NOISE_CHANNEL_WEIGHT, m_ChannelWeights, L_GHOST, PPOperators.SET);
		float nx = (Math.Sin(t * 0.29) * 0.5 + 0.5) * 0.3;
		float ny = (Math.Cos(t * 0.17) * 0.5 + 0.5) * 0.3;
		float spread = 40 * s;											// px from the picture
		float gx = spread * Math.Cos(t * 0.3) + 30 * f * Math.Sin(t * 9);
		float gy = spread * 0.6 * Math.Sin(t * 0.3) + 16 * f * Math.Cos(t * 7);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_NOISE_OFFSET_X, false, nx, L_GHOST, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_NOISE_OFFSET_Y, false, ny, L_GHOST, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_GHOST_OFFSET_X, false, gx, L_GHOST, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Ghost, PPEGhost.PARAM_GHOST_OFFSET_Y, false, gy, L_GHOST, PPOperators.ADD);

		// the view drifts out of focus and back, as vanilla's fever blur does but slower: a swell every quarter minute
		// or so, some deeper than others, sharp in between (in a scare, blurred hard)
		float swell = Math.Sin(t * 0.45) * 0.5 + 0.5;
		swell = swell * swell * swell;
		float depth = 0.65 + 0.35 * Math.Sin(t * 0.11 + 1.3);
		float focus = 0.3 * s * swell * depth + 0.25 * f;
		SetTargetValueFloat(PostProcessEffectType.GaussFilter, PPEGaussFilter.PARAM_INTENSITY, true, focus, L_FOCUS, PPOperators.ADD_RELATIVE);

		// the wet-lens waves (vanilla's rain-on-the-lens pass): broad, smooth and strong, so the whole view swims, without
		// the pass's own blur and per-line randomness (in a scare, as strong and fast as they go)
		float wavePower = Math.Clamp(s + 0.1 * f, 0, 1);
		float waveX1 = Math.Clamp(0.001 + 0.04 * s + 0.007 * f, 0.001, GEB_TRIP_WAVE_MAX);	// (rain's 0.004..0.009)
		float waveY1 = Math.Clamp(0.001 + 0.04 * s + 0.006 * f, 0.001, GEB_TRIP_WAVE_MAX);
		float waveX2 = Math.Clamp(0.001 + 0.035 * s + 0.008 * f, 0.001, GEB_TRIP_WAVE_MAX);
		float waveY2 = Math.Clamp(0.001 + 0.035 * s + 0.008 * f, 0.001, GEB_TRIP_WAVE_MAX);
		float speedX = Math.Clamp(4.5 + 5.5 * f, 0.5, 10);
		float speedY = Math.Clamp(3.5 + 6 * f, 0.5, 10);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_EFFPOWERTOP, false, wavePower, L_WAVES, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_EFFPOWERBOTTOM, false, wavePower, L_WAVES, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVEAMPX1, false, waveX1, L_WAVES, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVEAMPY1, false, waveY1, L_WAVES, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVEAMPX2, false, waveX2, L_WAVES, PPOperators.HIGHEST);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVEAMPY2, false, waveY2, L_WAVES, PPOperators.HIGHEST);
		// below vanilla's values, so set rather than raised: radians of wave across the view (near 1 the whole picture
		// only slides; much above 5 they turn jagged) and no per-line randomness (the tearing rain has)
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_PHASEPOSX, false, 5, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_PHASEPOSY, false, 4, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_PHASERANDX, false, 0, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_PHASERANDY, false, 0, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVSPDX1, false, speedX, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_WAVSPDY1, false, speedY, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_BLURPOWER, false, 0.05, L_WAVES, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.WetDistort, PPEWetDistort.PARAM_LOCALBLURPOWER, false, 0.05, L_WAVES, PPOperators.SET);
	}
};

// The wet-lens pass's wave heights go up to GEB_TRIP_WAVE_MAX instead of vanilla's 0.02. The PPE manager maps every
// request into a parameter's registered range and clamps it there, so 0.02 was a hard ceiling. Requests are mapped
// in and out of the same range, so rain's own values come out exactly as before.
modded class PPEWetDistort
{
	override void RegisterMaterialParameters()
	{
		super.RegisterMaterialParameters();
		RegisterParameterScalarFloat(PARAM_WAVEAMPX1, "WaveAmpX1", 0.005, 0.001, GEB_TRIP_WAVE_MAX);
		RegisterParameterScalarFloat(PARAM_WAVEAMPX2, "WaveAmpX2", 0.004, 0.001, GEB_TRIP_WAVE_MAX);
		RegisterParameterScalarFloat(PARAM_WAVEAMPY1, "WaveAmpY1", 0.009, 0.001, GEB_TRIP_WAVE_MAX);
		RegisterParameterScalarFloat(PARAM_WAVEAMPY2, "WaveAmpY2", 0.007, 0.001, GEB_TRIP_WAVE_MAX);
	}
};

// Registered the way vanilla asks mods to (PPERequesterRegistrations in pperequesterbank.c)
modded class PPERequesterRegistrations
{
	override protected void RegisterAdditionalRequesters()
	{
		super.RegisterAdditionalRequesters();
		PPERequesterBank.RegisterRequester(PPERequester_GebTrip);
	}
};
