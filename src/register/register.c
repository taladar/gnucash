
/*
 * register.c
 */

#include "register.h"

#define DATE_CELL_C  0
#define DATE_CELL_R  0

#define NUM_CELL_C  1
#define NUM_CELL_R  0

#define XFRM_CELL_C  2
#define XFRM_CELL_R  0

#define XTO_CELL_C  2
#define XTO_CELL_R  1

#define DESC_CELL_C  3
#define DESC_CELL_R  0

#define MEMO_CELL_C  3
#define MEMO_CELL_R  1

#define RECN_CELL_C  4
#define RECN_CELL_R  0

#define CRED_CELL_C  5
#define CRED_CELL_R  0

#define DEBT_CELL_C  6
#define DEBT_CELL_R  0

#define BALN_CELL_C  7
#define BALN_CELL_R  0

#define MAX_COLS 8

/* ================================= */

BasicRegister * xaccMallocBasicRegister (void)
{
   BasicRegister * reg;
   reg = (BasicRegister *) malloc (sizeof (BasicRegister));
   xaccInitBasicRegister (reg);
   return reg;
}

/* ================================= */

void xaccInitBasicRegister (BasicRegister *reg)
{
   Table * table;
   CellBlock *curs, *header;
   BasicCell *cell;

   /* define the header */

   header = xaccMallocCellBlock (1, MAX_COLS);
   reg->header = header;

   cell = (BasicCell *) xaccMallocDateCell();
   cell->width = 11;
   xaccAddCell (header, cell, 0, DATE_CELL_C);
   xaccSetBasicCellValue (cell, "Date");
   
   cell = xaccMallocTextCell();
   cell->width = 7;
   xaccAddCell (header, cell, 0, NUM_CELL_C);
   xaccSetBasicCellValue (cell, "Num");

   cell = xaccMallocTextCell();
   cell->width = 29;
   xaccAddCell (header, cell, 0, DESC_CELL_C);
   xaccSetBasicCellValue (cell, "Description");

   cell = xaccMallocRecnCell();
   cell->width = 1;
   xaccAddCell (header, cell, 0, RECN_CELL_C);
   xaccSetBasicCellValue (cell, "R");

   cell = (BasicCell *) xaccMallocPriceCell();
   cell->width = 9;
   xaccAddCell (header, cell, 0, CRED_CELL_C);
   xaccSetBasicCellValue (cell, "Credit");
   
   cell = (BasicCell *) xaccMallocPriceCell();
   cell->width = 9;
   xaccAddCell (header, cell, 0, DEBT_CELL_C);
   xaccSetBasicCellValue (cell, "Debit");

   cell = (BasicCell *) xaccMallocPriceCell();
   cell->width = 9;
   xaccAddCell (header, cell, 0, BALN_CELL_C);
   xaccSetBasicCellValue (cell, "Balance");

   
   /* --------------------------- */
   curs = xaccMallocCellBlock (2, MAX_COLS);
   reg->cursor = curs;
   
   cell = (BasicCell *) xaccMallocDateCell();
   cell->width = 9;
   xaccAddCell (curs, cell, DATE_CELL_R, DATE_CELL_C);
   reg->dateCell = cell;
   
   cell = xaccMallocTextCell();
   cell->width = 7;
   xaccAddCell (curs, cell, NUM_CELL_R, NUM_CELL_C);
   reg->numCell = cell;
   
   cell = xaccMallocTextCell();
   cell->width = 11;
   xaccAddCell (curs, cell, XFRM_CELL_R, XFRM_CELL_C);
   reg->xferCell = cell;
   
   cell = xaccMallocTextCell();
   cell->width = 9;
   xaccAddCell (curs, cell, DESC_CELL_R, DESC_CELL_C);
   reg->descCell = cell;
   
   cell = xaccMallocTextCell();
   cell->width = 9;
   xaccAddCell (curs, cell, MEMO_CELL_R, MEMO_CELL_C);
   reg->memoCell = cell;

   cell = xaccMallocRecnCell();
   cell->width = 1;
   xaccAddCell (curs, cell, RECN_CELL_R, RECN_CELL_C);
   reg->recnCell = cell;

   reg->creditCell = xaccMallocPriceCell();
   reg->creditCell->cell.width = 9;
   xaccAddCell (curs, &(reg->creditCell->cell), CRED_CELL_R, CRED_CELL_C);
   
   reg->debitCell = xaccMallocPriceCell();
   reg->debitCell->cell.width = 9;
   xaccAddCell (curs, &(reg->debitCell->cell), DEBT_CELL_R, DEBT_CELL_C);
   
   reg->balanceCell = xaccMallocPriceCell();
   reg->balanceCell->cell.width = 9;
   reg->balanceCell->cell.input_output = 0;
   xaccAddCell (curs, &(reg->balanceCell->cell), BALN_CELL_R, BALN_CELL_C);
   
   table =  xaccMallocTable (0, 0);
   table -> header = header;
   xaccSetCursor (table, curs);
   xaccInitTable (table, 5, 1);
   reg->table = table;
}

/* ============ END OF FILE ===================== */
