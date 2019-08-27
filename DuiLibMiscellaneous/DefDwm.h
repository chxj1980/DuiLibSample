
#include <windef.h>

#ifndef _DWMAPI_H_
#define _DWMAPI_H_

typedef struct DWM_BLUR_BEHIND
{
	DWORD dwFlags;
	BOOL bEnable;
	HRGN hRgnBlur;
	BOOL bTransitionOnMaxmized;
} DWM_BLUR_BEHIND;

typedef struct TAG_DWL_MARGINS
{
	int nxLeftWidth;
	int nxRightWidth;
	int nyTopHeight;
	int nyBottomHeight;
} DWM_MARGINS, * PDWM_MARGINS;

// Window attributes
enum DWMWINDOWATTRIBUTE
{
	DWMWA_NCRENDERING_ENABLED = 1,      // [get] Is non-client rendering enabled/disabled
	DWMWA_NCRENDERING_POLICY,           // [set] Non-client rendering policy
	DWMWA_TRANSITIONS_FORCEDISABLED,    // [set] Potentially enable/forcibly disable transitions
	DWMWA_ALLOW_NCPAINT,                // [set] Allow contents rendered in the non-client area to be visible on the DWM-drawn frame.
	DWMWA_CAPTION_BUTTON_BOUNDS,        // [get] Bounds of the caption button area in window-relative space.
	DWMWA_NONCLIENT_RTL_LAYOUT,         // [set] Is non-client content RTL mirrored
	DWMWA_FORCE_ICONIC_REPRESENTATION,  // [set] Force this window to display iconic thumbnails.
	DWMWA_FLIP3D_POLICY,                // [set] Designates how Flip3D will treat the window.
	DWMWA_EXTENDED_FRAME_BOUNDS,        // [get] Gets the extended frame bounds rectangle in screen space
	DWMWA_HAS_ICONIC_BITMAP,            // [set] Indicates an available bitmap when there is no better thumbnail representation.
	DWMWA_DISALLOW_PEEK,                // [set] Don't invoke Peek on the window.
	DWMWA_EXCLUDED_FROM_PEEK,           // [set] LivePreview exclusion information
	DWMWA_CLOAK,                        // [set] Cloak or uncloak the window
	DWMWA_CLOAKED,                      // [get] Gets the cloaked state of the window
	DWMWA_FREEZE_REPRESENTATION,        // [set] Force this window to freeze the thumbnail without live update
	DWMWA_LAST
};

// Non-client rendering policy attribute values
enum DWMNCRENDERINGPOLICY
{
	DWMNCRP_USEWINDOWSTYLE, // Enable/disable non-client rendering based on window style
	DWMNCRP_DISABLED,       // Disabled non-client rendering; window style is ignored
	DWMNCRP_ENABLED,        // Enabled non-client rendering; window style is ignored
	DWMNCRP_LAST
};

// Values designating how Flip3D treats a given window.
enum DWMFLIP3DWINDOWPOLICY
{
	DWMFLIP3D_DEFAULT,      // Hide or include the window in Flip3D based on window style and visibility.
	DWMFLIP3D_EXCLUDEBELOW, // Display the window under Flip3D and disabled.
	DWMFLIP3D_EXCLUDEABOVE, // Display the window above Flip3D and enabled.
	DWMFLIP3D_LAST
};

#define DWM_BB_ENABLE                 0x00000001
#define DWM_BB_BLURREGION             0x00000002
#define DWM_BB_TRANSITIONONMAXIMIZED  0x00000004

#define DWM_EC_DISABLECOMPOSITION     0x00000000
#define DWM_EC_ENABLECOMPOSITION      0x00000001
#endif // !_DWMAPI_H_
