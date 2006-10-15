%module sw_report_system
%{
/* Includes the header in the wrapper code */
#include <config.h>
#include <gnc-report.h>

SCM scm_init_sw_report_system_module (void);
%}

typedef int gint;

SCM gnc_report_find(gint id);
gint gnc_report_add(SCM report);
