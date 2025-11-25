/*           __        _
 *  ________/ /  ___ _(_)__  ___
 * / __/ __/ _ \/ _ `/ / _ \/ -_)
 * \__/\__/_//_/\_,_/_/_//_/\__/
 * 
 * Copyright (C) Clément Chaine
 * This file is part of ECAP5-DWBMMSC <https://github.com/ecap5/ECAP5-DWBMMSC>
 *
 * ECAP5-DWBMMSC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ECAP5-DWBMMSC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ECAP5-DWBMMSC.  If not, see <http://www.gnu.org/licenses/>.
 */

module tb_ecap5_dwbmmsc
(
  input   int          testcase,

  input   logic         clk_i,
  input   logic         rst_i,

  //=================================
  //    Memory interface

  input   logic[31:0]  wb_adr_i,
  output  logic[31:0]  wb_dat_o,
  input   logic[31:0]  wb_dat_i,
  input   logic        wb_we_i,
  input   logic[3:0]   wb_sel_i,
  input   logic        wb_stb_i,
  output  logic        wb_ack_o,
  input   logic        wb_cyc_i,
  output  logic        wb_stall_o,

  //=================================
  //    Output interface

  output  logic[7:0]   addr_o,
  output  logic        read_o,
  input   logic[31:0]  read_data_i,
  output  logic        write_o,
  output  logic[31:0]  write_data_o,
  output  logic[3:0]   sel_o
);

ecap5_dwbmmsc dut (
  .clk_i           (clk_i),
  .rst_i           (rst_i),

  .wb_adr_i   (wb_adr_i),
  .wb_dat_o   (wb_dat_o),
  .wb_dat_i   (wb_dat_i),
  .wb_we_i    (wb_we_i),
  .wb_sel_i   (wb_sel_i),
  .wb_stb_i   (wb_stb_i),
  .wb_ack_o   (wb_ack_o),
  .wb_cyc_i   (wb_cyc_i),
  .wb_stall_o (wb_stall_o),

  .addr_o       (addr_o),
  .read_o       (read_o),
  .read_data_i  (read_data_i),
  .write_o      (write_o),
  .write_data_o (write_data_o),
  .sel_o        (sel_o)
);

endmodule // tb_ecap5_dwbmmsc
