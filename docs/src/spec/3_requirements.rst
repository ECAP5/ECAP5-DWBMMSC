Requirements
============

.. |tab|   unicode:: U+00A0 .. NO-BREAK SPACE

External Interface Requirements
-------------------------------

.. list-table:: Control signals
  :header-rows: 1
  :width: 100%
  :widths: 10 10 10 70

  * - Name
    - Type
    - Width
    - Description

  * - clk_i
    - I
    - 1
    - Clock input.
  * - rst_i
    - I
    - 1
    - Hardware reset.

.. list-table:: Memory interface signals
  :header-rows: 1
  :width: 100%
  :widths: 10 10 10 70

  * - Name
    - Type
    - Width
    - Description

  * - wb_adr_i
    - I
    - 32
    - The address output array is used to pass binary address.
  * - wb_dat_i
    - I
    - 32
    - The data input array is used to pass binary data.
  * - wb_dat_o
    - O
    - 32
    - The data output array is used to pass binary data.
  * - wb_sel_i
    - I
    - 4
    - The select output array indicates where valid data is expected on the wb_dat_i signal array during READ cycles, and where it is placed on the wb_dat_o signal array during WRITE cycles. Each individual select signal correlates to one of four active bytes on the 32-bit data port.
  * - wb_we_i
    - I
    - 1
    - The write enable output indicates whether the current local bus cycle is a READ or WRITE cycle. This signal is negated during READ cycles and is asserted during WRITE cycles.
  * - wb_stb_i
    - I
    - 1
    - The strobe output indicates a valid data transfer cycle. It is used to qualify various other signals on the interface.
  * - wb_ack_o
    - O
    - 1
    - The acknowledge input, when asserted, indicates the normal termination of a bus cycle.
  * - wb_cyc_i
    - I
    - 1
    - The cycle output, when asserted, indicates that a valid bus cycle is in progress. This signal is asserted for the duration of all bus cycles.
  * - wb_stall_o
    - O
    - 1
    - The stall input indicates that current slave is not able to accept the transfer in the transaction queue.

.. list-table:: Internal interface signals
  :header-rows: 1
  :width: 100%
  :widths: 10 10 10 70

  * - Name
    - Type
    - Width
    - Description

  * - uart_rx_i
    - I
    - 1
    - This signal is sampled by the peripheral to receive data
  * - uart_tx_o
    - O
    - 1
    - This signal is driven by the peripheral to send data

Functional Requirements
-----------------------

Memory interface
^^^^^^^^^^^^^^^^

Wishbone protocol
`````````````````

The following requirements are extracted from the Wishbone specification.

.. requirement:: F_WISHBONE_DATASHEET_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall comply with the Wishbone Datasheet provided in section 2.1.

.. requirement:: F_WISHBONE_RESET_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall initialize itself at the rising edge of clk_i following the assertion of rst_i.

.. requirement:: F_WISHBONE_RESET_02
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall stay in the initialization state until the rising edge of clk_i following the deassertion of rst_i.

.. requirement:: F_WISHBONE_TRANSFER_CYCLE_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall only respond to transfer cycles when wb_cyc_i is asserted.

.. requirement:: F_WISHBONE_HANDSHAKE_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall assert the wb_ack_o signal in response to the logical AND of wb_cyc_i and wb_stb_i.

.. requirement:: F_WISHBONE_READ_CYCLE_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall conform to the READ cycle detailed in the figure below.

.. figure:: ../assets/wishbone-read.svg
   :align: center
   
   Timing diagram of the wishbone read cycle

.. requirement:: F_WISHBONE_WRITE_CYCLE_01
  :derivedfrom: U_MEMORY_INTERFACE_01

  The memory interface shall conform to the WRITE cycle detailed in figure below.

.. figure:: ../assets/wishbone-write.svg
   :align: center
   
   Timing diagram of the wishbone write cycle

.. requirement:: F_WISHBONE_TIMING_01
  :rationale: As long as the memory interface is designed within the clock domain of clk_i, the requirement will be satisfied by using the place and route tool.
  :derivedfrom: U_MEMORY_INTERFACE_01

  The clock input clk_i shall coordinate all activites for the internal logic within the memory interface. All output signals of the memory interface shall be registered at the rising edge of clk_i. All input signals of the memory interface shall be stable before the rising edge of clk_i.

Non-functional Requirements
---------------------------

N/A
