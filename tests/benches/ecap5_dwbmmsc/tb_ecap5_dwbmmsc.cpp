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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <svdpi.h>

#include "Vtb_ecap5_dwbmmsc.h"
#include "testbench.h"

enum CondId {
  COND_output = 0,
  COND_wishbone,
  __CondIdEnd
};

enum TestcaseId {
  T_RESET = 1,
  T_READ,
  T_WRITE
};

class TB_Ecap5_dwbmmsc : public Testbench<Vtb_ecap5_dwbmmsc> {
public:
  void reset() {
    this->_nop();

    this->core->rst_i = 1;
    for(int i = 0; i < 5; i++) {
      this->tick();
    }
    this->core->rst_i = 0;

    Testbench<Vtb_ecap5_dwbmmsc>::reset();
  }
  
  void _nop() {
    this->core->wb_adr_i = 0;
    this->core->wb_dat_i = 0;
    this->core->wb_we_i = 0;
    this->core->wb_sel_i = 0;
    this->core->wb_stb_i = 0;
    this->core->wb_cyc_i = 0;
  }

  void read(uint32_t addr) {
    this->core->wb_adr_i = addr;
    this->core->wb_dat_i = 0;
    this->core->wb_we_i = 0;
    this->core->wb_sel_i = 0xF;
    this->core->wb_stb_i = 1;
    this->core->wb_cyc_i = 1;
  }

  void write(uint32_t addr, uint32_t data) {
    this->core->wb_adr_i = addr;
    this->core->wb_dat_i = data;
    this->core->wb_we_i = 1;
    this->core->wb_sel_i = 0xF;
    this->core->wb_stb_i = 1;
    this->core->wb_cyc_i = 1;
  }
};

void tb_ecap5_dwbmmsc_reset(TB_Ecap5_dwbmmsc * tb) {
  Vtb_ecap5_dwbmmsc * core = tb->core;
  core->testcase = T_RESET;

  // The following actions are performed in this test :
  //    tick 0. Reset (core is in reset)
  //    tick 1. Still in reset (core is still in reset)
  
  //=================================
  //      Tick (0)
  
  tb->reset();

  //`````````````````````````````````
  //      Set inputs
  
  core->rst_i = 1;

  //=================================
  //      Tick (1)
  
  tb->tick();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 0));
  tb->check(COND_output,   (core->read_o   == 0) &&
                           (core->write_o  == 0));

  //=================================
  //      Tick (1)
  
  tb->tick();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 0));
  tb->check(COND_output,   (core->read_o   == 0) &&
                           (core->write_o  == 0));

  //`````````````````````````````````
  //      Formal Checks 
  
  CHECK("tb_ecap5_dwbmmsc.reset.01",
      tb->conditions[COND_output],
      "Failed to implement the output logic", tb->err_cycles[COND_output]);

  CHECK("tb_ecap5_dwbmmsc.reset.02",
      tb->conditions[COND_wishbone],
      "Failed to implement the wishbone protocol", tb->err_cycles[COND_wishbone]);
}

void tb_ecap5_dwbmmsc_read(TB_Ecap5_dwbmmsc * tb) {
  Vtb_ecap5_dwbmmsc * core = tb->core;
  core->testcase = T_READ;

  //=================================
  //      Tick (0)
  
  tb->reset();

  //`````````````````````````````````
  //      Set inputs
  
  tb->check(COND_output, (core->read_o == 0) &&
                         (core->write_o == 0));
  
  uint32_t addr = rand();
  tb->read(addr);

  // Async logic
  core->eval();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_output, (core->read_o == 1) &&
                         (core->addr_o == addr) &&
                         (core->write_o == 0));

  //=================================
  //      Tick (1)
  
  tb->tick();

  //`````````````````````````````````
  //      Set inputs
  
  tb->_nop();
  core->wb_cyc_i = 1;

  uint32_t data = rand();
  core->read_data_i = data;

  // Async logic
  core->eval();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 1) &&
                           (core->wb_dat_o == data));
  tb->check(COND_output, (core->read_o == 0) &&
                         (core->write_o == 0));

  //=================================
  //      Tick (2)
  
  tb->tick();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 0));

  //`````````````````````````````````
  //      Set inputs
  
  core->wb_cyc_i = 0;

  core->read_data_i = 0;

  //=================================
  //      Tick (3)
  
  tb->tick();

  //`````````````````````````````````
  //      Formal Checks 
  
  CHECK("tb_ecap5_dwbmmsc.read.01",
      tb->conditions[COND_output],
      "Failed to implement the output logic", tb->err_cycles[COND_output]);

  CHECK("tb_ecap5_dwbmmsc.read.02",
      tb->conditions[COND_wishbone],
      "Failed to implement the wishbone protocol", tb->err_cycles[COND_wishbone]);
}

void tb_ecap5_dwbmmsc_write(TB_Ecap5_dwbmmsc * tb) {
  Vtb_ecap5_dwbmmsc * core = tb->core;
  core->testcase = T_WRITE;

  //=================================
  //      Tick (0)
  
  tb->reset();

  //`````````````````````````````````
  //      Set inputs
  
  tb->check(COND_output, (core->read_o == 0) &&
                           (core->write_o == 0));
  
  uint32_t addr = rand();
  uint32_t data = rand();
  tb->write(addr, data);

  // Async logic
  core->eval();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_output, (core->read_o == 0) &&
                         (core->addr_o == addr) &&
                         (core->write_o == 1) &&
                         (core->write_data_o == data));

  //=================================
  //      Tick (1)
  
  tb->tick();

  //`````````````````````````````````
  //      Set inputs
  
  tb->_nop();
  core->wb_cyc_i = 1;

  // Async logic
  core->eval();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 1));
  tb->check(COND_output, (core->read_o == 0) &&
                         (core->write_o == 0));

  //=================================
  //      Tick (2)
  
  tb->tick();

  //`````````````````````````````````
  //      Checks 
  
  tb->check(COND_wishbone, (core->wb_ack_o == 0));

  //`````````````````````````````````
  //      Set inputs
  
  core->wb_cyc_i = 0;

  //=================================
  //      Tick (3)
  
  tb->tick();

  //`````````````````````````````````
  //      Formal Checks 
  
  CHECK("tb_ecap5_dwbmmsc.write.01",
      tb->conditions[COND_output],
      "Failed to implement the output logic", tb->err_cycles[COND_output]);

  CHECK("tb_ecap5_dwbmmsc.write.02",
      tb->conditions[COND_wishbone],
      "Failed to implement the wishbone protocol", tb->err_cycles[COND_wishbone]);
}

int main(int argc, char ** argv, char ** env) {
  srand(time(NULL));
  Verilated::traceEverOn(true);

  bool verbose = parse_verbose(argc, argv);
  verbose=1;

  TB_Ecap5_dwbmmsc * tb = new TB_Ecap5_dwbmmsc;
  tb->open_trace("waves/ecap5_dwbmmsc.vcd");
  tb->open_testdata("testdata/ecap5_dwbmmsc.csv");
  tb->set_debug_log(verbose);
  tb->init_conditions(__CondIdEnd);

  /************************************************************/

  tb_ecap5_dwbmmsc_reset(tb);
  tb_ecap5_dwbmmsc_read(tb);
  tb_ecap5_dwbmmsc_write(tb);

  /************************************************************/

  printf("[WB_INTERFACE]: ");
  if(tb->success) {
    printf("Done\n");
  } else {
    printf("Failed\n");
  }

  delete tb;
  exit(EXIT_SUCCESS);
}
