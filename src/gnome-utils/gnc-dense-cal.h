#ifndef _DENSECAL_H_
#define _DENSECAL_H_

/********************************************************************\
 * gnc-dense-cal.h : a custom densely-dispalyed calendar widget     *
 * Copyright (C) 2002 Joshua Sled <jsled@asynchronous.org>          *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652       *
 * Boston, MA  02111-1307,  USA       gnu@gnu.org                   *
\********************************************************************/

#include <gdk/gdk.h>
#include <gtk/gtkadjustment.h>
#include <gtk/gtkwidget.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GNC_DENSE_CAL(obj)          GTK_CHECK_CAST (obj, gnc_dense_cal_get_type (), GncDenseCal)
#define GNC_DENSE_CAL_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, gnc_dense_cal_get_type (), GncDenseCalClass)
#define GNC_IS_DENSE_CAL(obj)       GTK_CHECK_TYPE (obj, gnc_dense_cal_get_type ())

typedef struct _GncDenseCal        GncDenseCal;
typedef struct _GncDenseCalClass   GncDenseCalClass;

typedef struct _gdc_month_coords {
        gint x, y;
} gdc_month_coords;

struct _GncDenseCal
{
        GtkWidget widget;

        gboolean initialized;

        gboolean showPopup;
        GtkWindow *transPopup;

        gint min_x_scale;
        gint min_y_scale;

        gint x_scale;
        gint y_scale;

        gint numMonths;
        gint monthsPerCol;
        gint num_weeks; // computed

        GDateMonth month;
        gint year;
        gint firstOfMonthOffset;

        gint leftPadding;
        gint topPadding;

        gboolean needInitMonthLabels;
        gdc_month_coords monthPositions[12];
        GdkFont *monthLabelFont;
        GdkFont *dayLabelFont;
        GdkPixmap *monthLabels[12];

        enum GDC_COLORS {
                MONTH_THIS = 0,
                MONTH_THAT,
                MAX_COLORS };
        GdkColor weekColors[MAX_COLORS];

        guint label_lbearing;
        guint label_ascent;
        guint label_width;
        guint label_height;
        guint dayLabelHeight;

        guint lastMarkTag;

        /**
         * A GList of gdc_mark_data structs, one for each active/valid markTag.
         **/
        GList *markData;
        int numMarks;
        // array of GList*s of per-cell markings.
        GList **marks;
};

struct _GncDenseCalClass
{
        GtkWidgetClass parent_class;
        void (*marks_lost_cb)( GncDenseCal *dcal, gpointer user_data );
};

typedef struct _gdc_mark_data {
        gchar *name;
        gchar *info;
        guint tag;
        // GdkColor markStyle;
        /**
         * A GList of the dcal->marks indexes containing this mark.
         **/
        GList *ourMarks;
} gdc_mark_data;

GtkWidget*     gnc_dense_cal_new                    ();
GtkType        gnc_dense_cal_get_type               (void);

void gnc_dense_cal_set_month( GncDenseCal *dcal, GDateMonth mon );
/**
 * @param year Julian year: 2000 = 2000AD.
 **/
void gnc_dense_cal_set_year( GncDenseCal *dcal, guint year );
void gnc_dense_cal_set_num_months( GncDenseCal *dcal, guint num_months );
void gnc_dense_cal_set_months_per_col( GncDenseCal *dcal, guint monthsPerCol );

guint gnc_dense_cal_get_num_months( GncDenseCal *dcal );
GDateMonth gnc_dense_cal_get_month( GncDenseCal *dcal );
GDateYear gnc_dense_cal_get_year( GncDenseCal *dcal );

guint gnc_dense_cal_mark( GncDenseCal *dcal,
                          guint size, GDate **daysArray,
                          gchar *name, gchar *info );
void gnc_dense_cal_mark_remove( GncDenseCal *dcal, guint markToRemove );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DENSECAL_H_ */
