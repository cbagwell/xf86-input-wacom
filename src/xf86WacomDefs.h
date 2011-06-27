/*
 * Copyright 1995-2002 by Frederic Lepied, France. <Lepied@XFree86.org>
 * Copyright 2002-2010 by Ping Cheng, Wacom. <pingc@wacom.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __XF86_XF86WACOMDEFS_H
#define __XF86_XF86WACOMDEFS_H

/*****************************************************************************
 * General Defines
 ****************************************************************************/
#include <asm/types.h>
#include <linux/input.h>
#define MAX_USB_EVENTS 32

/* vendor IDs on the kernel device */
#define WACOM_VENDOR_ID 0x056a
#define WALTOP_VENDOR_ID 0x172F
#define NTRIG_VENDOR_ID 0x1b96
#define HANWANG_VENDOR_ID 0x0b57
#define LENOVO_VENDOR_ID 0x17ef

#define DEFAULT_SUPPRESS 2      /* default suppress */
#define MAX_SUPPRESS 100        /* max value of suppress */
#define BUFFER_SIZE 256         /* size of reception buffer */
#define MAXTRY 3                /* max number of try to receive magic number */
#define MIN_ROTATION  -900      /* the minimum value of the marker pen rotation */
#define MAX_ROTATION_RANGE 1800 /* the maximum range of the marker pen rotation */
#define MAX_ABS_WHEEL 1023      /* the maximum value of absolute wheel */

#define MIN_PAD_RING 0		/* I4 absolute scroll ring min value */
#define MAX_PAD_RING 71		/* I4 absolute scroll ring max value */

/* I4 cursor tool has a rotation offset of 175 degrees */
#define INTUOS4_CURSOR_ROTATION_OFFSET 175

/* Default max distance to the tablet at which a proximity-out event is generated for
 * cursor device (e.g. mouse). 
 */
#define PROXOUT_INTUOS_DISTANCE		10
#define PROXOUT_GRAPHIRE_DISTANCE	42

/* 2.6.28 */

#ifndef BTN_TOOL_DOUBLETAP
#define BTN_TOOL_DOUBLETAP 0x14d
#endif

#ifndef BTN_TOOL_TRIPLETAP
#define BTN_TOOL_TRIPLETAP 0x14e
#endif

/* 2.6.30 */

#ifndef ABS_MT_POSITION_X
#define ABS_MT_POSITION_X 0x35
#endif

#ifndef ABS_MT_POSITION_Y
#define ABS_MT_POSITION_Y 0x36
#endif

#ifndef ABS_MT_TRACKING_ID
#define ABS_MT_TRACKING_ID 0x39
#endif

/* 2.6.33 */

#ifndef ABS_MT_PRESSURE
#define ABS_MT_PRESSURE 0x3a
#endif

/* 2.6.36 */

#ifndef ABS_MT_SLOT
#define ABS_MT_SLOT 0x2f
#endif

/* defines to discriminate second side button and the eraser */
#define ERASER_PROX     4
#define OTHER_PROX      1

/* to access kernel defined bits */
#define BIT(x)		(1UL<<((x) & (BITS_PER_LONG - 1)))
#define BITS_PER_LONG	(sizeof(long) * 8)
#define NBITS(x)	((((x)-1)/BITS_PER_LONG)+1)
#define ISBITSET(x,y)	((x)[LONG(y)] & BIT(y))
#define SETBIT(x,y)	((x)[LONG(y)] |= BIT(y))
#define CLEARBIT(x,y)	((x)[LONG(y)] &= ~BIT(y))
#define OFF(x)		((x)%BITS_PER_LONG)
#define LONG(x)		((x)/BITS_PER_LONG)

/**
 * Test if the mask is set in the given bitfield.
 * @return TRUE if set or FALSE otherwise.
 */
#define MaskIsSet(bitfield, mask) !!(((bitfield) & (mask)) == (mask))
/**
 * Set the given mask for the given bitfield.
 */
#define MaskSet(bitfield, mask) ((bitfield) |= (mask))
/**
 * Clear the given mask from the given bitfield
 */
#define MaskClear(bitfield, mask) ((bitfield) &= ~(mask))

/******************************************************************************
 * Forward Declarations
 *****************************************************************************/

typedef struct _WacomModel WacomModel, *WacomModelPtr;
typedef struct _WacomDeviceRec WacomDeviceRec, *WacomDevicePtr;
typedef struct _WacomDeviceState WacomDeviceState, *WacomDeviceStatePtr;
typedef struct _WacomChannel  WacomChannel, *WacomChannelPtr;
typedef struct _WacomCommonRec WacomCommonRec, *WacomCommonPtr;
typedef struct _WacomFilterState WacomFilterState, *WacomFilterStatePtr;
typedef struct _WacomDeviceClass WacomDeviceClass, *WacomDeviceClassPtr;
typedef struct _WacomTool WacomTool, *WacomToolPtr;
typedef struct _WacomToolArea WacomToolArea, *WacomToolAreaPtr;

/******************************************************************************
 * WacomModel - model-specific device capabilities
 *****************************************************************************/

struct _WacomModel
{
	const char* name;

	void (*Initialize)(WacomCommonPtr common, const char* id, float version);
	void (*GetResolution)(InputInfoPtr pInfo);
	int (*GetRanges)(InputInfoPtr pInfo);
	int (*Start)(InputInfoPtr pInfo);
	int (*Parse)(InputInfoPtr pInfo, const unsigned char* data, int len);
	int (*DetectConfig)(InputInfoPtr pInfo);
};

/******************************************************************************
 * WacomDeviceRec
 *****************************************************************************/

/* these device IDs are reported through ABS_MISC for Protocol 4 devices */
#define DEVICE_ID(flags) ((flags) & 0xff)
#define STYLUS_DEVICE_ID	0x02
#define TOUCH_DEVICE_ID		0x03
#define CURSOR_DEVICE_ID	0x06
#define ERASER_DEVICE_ID	0x0A
#define PAD_DEVICE_ID		0x0F

#define STYLUS_ID		0x00000001
#define TOUCH_ID		0x00000002
#define CURSOR_ID		0x00000004
#define ERASER_ID		0x00000008
#define PAD_ID			0x00000010

/* Each tablet may have one or more of the following
 * features */
#define WCM_PEN			0x00000001 /* Tablet supports pens */
#define WCM_PAD			0x00000002 /* Has a pad tool */

#define WCM_1FGT		0x00000004 /* One finger touch */
#define WCM_2FGT		0x00000008 /* Two finger touch */
#define WCM_STRIP		0x00000010 /* Tablet has menu strip (e.g.
					      Intuos3) */
#define WCM_RING		0x00000020 /* Tablet has touch ring (e.g.
					      Intuos4) */
#define WCM_DUALINPUT		0x00000040 /* Supports two tools on the
					      tablet simultaneously (Intuos
					      1 and 2) */
#define WCM_ROTATION		0x00000080 /* Needs to convert mouse tool
					      tilt to rotation */
#define WCM_LCD			0x00000100 /* Cintiqs and other display
					      tablets */
#define WCM_TPC			(0x00000200 | WCM_LCD) /* TabletPC (special
							  button handling,
							  always an LCD) */
#define WCM_PENTOUCH		0x00000400 /* Tablet supports pen and touch */
#define TabletHasFeature(common, feature) (((common)->tablet_type & (feature)) != 0)
#define TabletSetFeature(common, feature) ((common)->tablet_type |= (feature))

#define ABSOLUTE_FLAG		0x00000100
#define BAUD_19200_FLAG		0x00000400
#define BUTTONS_ONLY_FLAG	0x00000800

#define IsCursor(priv) (DEVICE_ID((priv)->flags) == CURSOR_ID)
#define IsStylus(priv) (DEVICE_ID((priv)->flags) == STYLUS_ID)
#define IsTouch(priv)  (DEVICE_ID((priv)->flags) == TOUCH_ID)
#define IsEraser(priv) (DEVICE_ID((priv)->flags) == ERASER_ID)
#define IsPad(priv)    (DEVICE_ID((priv)->flags) == PAD_ID)
#define IsPen(priv)    (IsStylus(priv) || IsEraser(priv))

#define IsUSBDevice(common) ((common)->wcmDevCls == &gWacomUSBDevice)

#define FILTER_PRESSURE_RES	2048	/* maximum points in pressure curve */
#define WCM_MAX_BUTTONS		32	/* maximum number of tablet buttons */
#define WCM_MAX_MOUSE_BUTTONS	16	/* maximum number of buttons-on-pointer
                                         * (which are treated as mouse buttons,
                                         * not as keys like tablet menu buttons). 
					 * For backword compability support, 
					 * tablet buttons besides the strips are
					 * treated as buttons */

/* get/set/property */
typedef struct _PROPINFO PROPINFO;

struct _PROPINFO
{
	Atom wcmProp;
	char paramName[32];
	int nParamID;
	int nFormat;
	int nSize;
	int nDefault;
};

struct _WacomDeviceRec
{
	char *name;		/* Do not move, same offset as common->device_path. Used by DBG macro */
	/* configuration fields */
	struct _WacomDeviceRec *next;
	InputInfoPtr pInfo;
	int debugLevel;

	unsigned int flags;	/* various flags (type, abs, touch...) */
	int topX;		/* X top in device coordinates */
	int topY;		/* Y top in device coordinates */
	int bottomX;		/* X bottom in device coordinates */
	int bottomY;		/* Y bottom in device coordinates */
	int resolX;             /* X resolution */
	int resolY;             /* Y resolution */
	int maxX;	        /* tool physical maxX in device coordinates*/
	int maxY;	        /* tool physical maxY in device coordinates*/
	double factorX;		/* X factor */
	double factorY;		/* Y factor */
	unsigned int serial;	/* device serial number this device takes (if 0, any serial is ok) */
	unsigned int cur_serial; /* current serial in prox */
	int maxWidth;		/* max active screen width in screen coords */
	int maxHeight;		/* max active screen height in screen coords */
	int leftPadding;	/* left padding for virtual tablet in device coordinates*/
	int topPadding;		/* top padding for virtual tablet in device coordinates*/
	/*  map zero based internal buttons to one based X buttons */
	int button[WCM_MAX_BUTTONS];
	/* map one based X buttons to keystrokes */
	unsigned keys[WCM_MAX_BUTTONS+1][256];
	int relup;
	int reldn;
	int wheelup;
	int wheeldn;
	/* keystrokes assigned to wheel events (default is the buttons above).
	 * Order is relup, reldwn, wheelup, wheeldn. Like 'keys', this array
	 * is one-indexed */
	unsigned wheel_keys[4+1][256];

	int striplup;
	int stripldn;
	int striprup;
	int striprdn;
	/* keystrokes assigned to strip events (default is the buttons above).
	 * Order is striplup, stripldn, striprup, striprdn. Like 'keys', this
	 * array is one-indexed */
	unsigned strip_keys[4+1][256];
	int nbuttons;           /* number of buttons for this subdevice */
	int naxes;              /* number of axes */
				/* FIXME: always 6, and the code relies on that... */

	WacomCommonPtr common;  /* common info pointer */

	/* state fields in device coordinates */
	int currentX;           /* current X position */
	int currentY;           /* current Y position */
	int currentSX;          /* current screen X position in screen coords */
	int currentSY;          /* current screen Y position in screen coords */
	int oldX;               /* previous X position */
	int oldY;               /* previous Y position */
	int oldZ;               /* previous pressure */
	int oldCapacity;        /* previous capacity */
	int oldTiltX;           /* previous tilt in x direction */
	int oldTiltY;           /* previous tilt in y direction */    
	int oldWheel;           /* previous wheel value */    
	int oldRot;             /* previous rotation value */
	int oldStripX;          /* previous left strip value */
	int oldStripY;          /* previous right strip value */
	int oldThrottle;        /* previous throttle value */
	int oldButtons;         /* previous buttons state */
	int oldProximity;       /* previous proximity */
	int oldCursorHwProx;	/* previous cursor hardware proximity */
	int old_device_id;	/* last in prox device id */
	unsigned int old_serial;/* last in prox tool serial number */
	int devReverseCount;	/* Relative ReverseConvert called twice each movement*/

	/* JEJ - throttle */
	int throttleStart;      /* time in ticks for last wheel movement */
	int throttleLimit;      /* time in ticks for next wheel movement */
	int throttleValue;      /* current throttle value */

	/* JEJ - filters */
	int pPressCurve[FILTER_PRESSURE_RES + 1]; /* pressure curve */
	int nPressCtrl[4];      /* control points for curve */
	int minPressure;	/* the minimum pressure a pen may hold */

	WacomToolPtr tool;         /* The common tool-structure for this device */

	int isParent;		/* set to 1 if the device is not auto-hotplugged */

	/* property handlers to listen to for action properties */
	Atom btn_actions[WCM_MAX_BUTTONS];
	Atom wheel_actions[4];
	Atom strip_actions[4];

	OsTimerPtr serial_timer; /* timer used for serial number property update */
};

/******************************************************************************
 * WacomDeviceState
 *****************************************************************************/

#define MAX_SAMPLES	20
#define DEFAULT_SAMPLES 4

struct _WacomDeviceState
{
	InputInfoPtr pInfo;
	int device_id;		/* tool id reported from the physical device */
	int device_type;
	unsigned int serial_num;
	int x;
	int y;
	int buttons;
	int pressure;
	int capacity;
	int tiltx;
	int tilty;
	int stripx;
	int stripy;
	int rotation;
	int abswheel;
	int relwheel;
	int distance;
	int throttle;
	int proximity;
	int sample;	/* wraps every 24 days */
};

struct _WacomFilterState
{
        int npoints;
        int x[MAX_SAMPLES];
        int y[MAX_SAMPLES];
        int tiltx[MAX_SAMPLES];
        int tilty[MAX_SAMPLES];
        int sample[MAX_SAMPLES];
};

struct _WacomChannel
{
	/* data stored in this structure is raw data from the tablet, prior
	 * to transformation and user-defined filtering. Suppressed values
	 * will not be included here, and hardware filtering may occur between
	 * the work stage and the valid state. */

	WacomDeviceState work;                         /* next state */

	/* the following union contains the current known state of the
	 * device channel, as well as the previous MAX_SAMPLES states
	 * for use in detecting hardware defects, jitter, trends, etc. */
	union
	{
		WacomDeviceState state;                /* current state */
		WacomDeviceState states[MAX_SAMPLES];  /* states 0..MAX */
	} valid;

	int nSamples;
	WacomFilterState rawFilter;
};

/******************************************************************************
 * WacomDeviceClass
 *****************************************************************************/

struct _WacomDeviceClass
{
	Bool (*Detect)(InputInfoPtr pInfo); /* detect device */
	Bool (*ParseOptions)(InputInfoPtr pInfo); /* parse class-specific options */
	Bool (*Init)(InputInfoPtr pInfo, char* id, float *version);   /* initialize device */
	int  (*ProbeKeys)(InputInfoPtr pInfo); /* set the bits for the keys supported */
};

extern WacomDeviceClass gWacomUSBDevice;
extern WacomDeviceClass gWacomISDV4Device;

/******************************************************************************
 * WacomCommonRec
 *****************************************************************************/

#define TILT_REQUEST_FLAG       1
#define TILT_ENABLED_FLAG       2

#define MAX_CHANNELS 3
#define PAD_CHANNEL (MAX_CHANNELS-1)
#define MAX_FINGERS  2

typedef struct {
	int wcmZoomDistance;	       /* minimum distance for a zoom touch gesture */
	int wcmZoomDistanceDefault;    /* default minimum distance for a zoom touch gesture */
	int wcmScrollDistance;	       /* minimum motion before sending a scroll gesture */
	int wcmScrollDirection;	       /* store the vertical or horizontal bit in use */
	int wcmScrollDistanceDefault;  /* default minimum motion before sending a scroll gesture */
	int wcmGestureUsed;	       /* retain used gesture count within one in-prox event */
	int wcmTapTime;	   	       /* minimum time between taps for a right click */
	int wcmTapTimeDefault;         /* default minimum time between taps for a right click */
} WacomGesturesParameters;

enum WacomProtocol {
	WCM_PROTOCOL_GENERIC,
	WCM_PROTOCOL_4,
	WCM_PROTOCOL_5
};

struct _WacomCommonRec 
{
	/* Do not move device_path, same offset as priv->name. Used by DBG macro */
	char* device_path;           /* device file name */
	dev_t min_maj;               /* minor/major number */
	unsigned char wcmFlags;     /* various flags (handle tilt) */
	int debugLevel;
	int vendor_id;		     /* Vendor ID */
	int tablet_id;		     /* USB tablet ID */
	int tablet_type;	     /* bitmask of tablet features (WCM_LCD, WCM_PEN, etc) */
	int fd;                      /* file descriptor to tablet */
	int fd_refs;                 /* number of references to fd; if =0, fd is invalid */
	unsigned long wcmKeys[NBITS(KEY_MAX)]; /* supported tool types for the device */
	WacomDevicePtr wcmTouchDevice; /* The pointer for pen to access the
					  touch tool of the same device id */
	Bool wcmPenInProx;      /* Keep pen in-prox state for touch tool */

	/* These values are in tablet coordinates */
	int wcmMaxX;                 /* tablet max X value */
	int wcmMaxY;                 /* tablet max Y value */
	int wcmMaxZ;                 /* tablet max Z value */
	int wcmMaxTouchX;            /* touch panel max X value */
	int wcmMaxTouchY;            /* touch panel max Y value */
	int wcmResolX;		     /* pen tool X resolution in points/m */
	int wcmResolY;		     /* pen tool Y resolution in points/m */
	int wcmTouchResolX;	     /* touch X resolution in points/m */
	int wcmTouchResolY;	     /* touch Y resolution in points/m */
	                             /* tablet Z resolution is equivalent
	                              * to wcmMaxZ which is equal to 100% pressure */
	int wcmMaxCapacity;	     /* max capacity value */
	int wcmMaxDist;              /* tablet max distance value */
	int wcmMaxtiltX;	     /* styli max tilt in X directory */ 
	int wcmMaxtiltY;	     /* styli max tilt in Y directory */ 

	int wcmMaxStripX;            /* Maximum fingerstrip X */
	int wcmMaxStripY;            /* Maximum fingerstrip Y */

	int nbuttons;                /* total number of buttons */
	int padkey_code[WCM_MAX_BUTTONS];/* hardware codes for buttons */
	int npadkeys;                /* number of pad keys in the above array */

	WacomDevicePtr wcmDevices;   /* list of devices sharing same port */
	int wcmPktLength;            /* length of a packet */
	int wcmProtocolLevel;        /* Wacom Protocol used */
	float wcmVersion;            /* ROM version */
	int wcmRotate;               /* rotate screen (for TabletPC) */
	int wcmThreshold;            /* Threshold for button pressure */
	WacomChannel wcmChannel[MAX_CHANNELS]; /* channel device state */

	WacomDeviceClassPtr wcmDevCls; /* device class functions */
	WacomModelPtr wcmModel;        /* model-specific functions */
	int wcmTPCButton;	     /* set Tablet PC button on/off */
	int wcmTouch;	             /* disable/enable touch event */
	int wcmTouchDefault;	     /* default to disable when not supported */
	int wcmGesture;	     	     /* disable/enable touch gesture */
	int wcmGestureDefault;       /* default touch gesture to disable when not supported */
	int wcmGestureMode;	       /* data is in Gesture Mode? */
	WacomDeviceState wcmGestureState[MAX_FINGERS]; /* inital state when in gesture mode */
	int wcmCapacity;	     /* disable/enable capacity */
	int wcmCapacityDefault;      /* default to -1 when capacity isn't supported/disabled */
				     /* 3 when capacity is supported */
	WacomGesturesParameters wcmGestureParameters;
	int wcmMaxCursorDist;	     /* Max mouse distance reported so far */
	int wcmCursorProxoutDist;    /* Max mouse distance for proxy-out max/256 units */
	int wcmCursorProxoutDistDefault; /* Default max mouse distance for proxy-out */
	int wcmSuppress;        	 /* transmit position on delta > supress */
	int wcmRawSample;	     /* Number of raw data used to filter an event */

	int bufpos;                        /* position with buffer */
	unsigned char buffer[BUFFER_SIZE]; /* data read from device */

	void *private;		     /* backend-specific information */

	WacomToolPtr wcmTool; /* List of unique tools */
	WacomToolPtr serials; /* Serial numbers provided at startup*/

	/* DO NOT TOUCH THIS. use wcmRefCommon() instead */
	int refcnt;			/* number of devices sharing this struct */
};

#define HANDLE_TILT(comm) ((comm)->wcmFlags & TILT_ENABLED_FLAG)

/******************************************************************************
 * WacomTool
 *****************************************************************************/
struct _WacomTool
{
	WacomToolPtr next; /* Next tool in list */

	int typeid; /* Tool type */
	unsigned int serial; /* Serial id, 0 == no serial id */
	Bool enabled;
	char *name;

	InputInfoPtr device; /* The InputDevice connected to this tool */
};

#endif /*__XF86_XF86WACOMDEFS_H */

/* vim: set noexpandtab tabstop=8 shiftwidth=8: */
