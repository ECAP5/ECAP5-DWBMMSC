Introduction
============

Purpose
-------

This documents aims at defining the requirements for ECAP5-DWBMMSC as well as describing its architecture. Both user and product requirements will be covered.

Intended Audience and Use
-------------------------

This document targets hardware engineers who shall implement ECAP5-DWBMMSC by refering to the described architecture. It is also intended for system engineers working on the integration of ECAP5-DWBMMSC in ECAP5. Finally, this document shall be used as a technical reference by software engineers configuring ECAP5-DWBMMSC through hardware-software interfaces.

Product Scope
-------------

ECAP5-DWBMMSC is Wishbone memory-mapped single-cycle interface module

Conventions
-----------

Requirement format
^^^^^^^^^^^^^^^^^^

This document details requirements with the following format :

.. list-table:: Sample requirement
  :width: 100%
  :widths: 10 90

  * - **ID**
    - Requirement_ID

  * - **Description**
    - Requirement description

  * - **Rationale**
    - Requirement rationale

  * - **DerivedFrom**
    - Other_Requirement_ID

with requirement IDs having the following format :

  * ``U_*``: User requirements
  * ``I_*``: External interface requirements
  * ``F_*``: Functional requirements
  * ``N_*``: Non-Functional requirements
  * ``A_*``: Architecture requirements

The requirement hierarchy and traceability scheme is detailed in the following figure.

.. figure:: ../assets/traceability.svg
   :align: center

   Requirement hierarchy and traceability


Definitions and Abbreviations
-----------------------------

References
----------

.. list-table::
  :header-rows: 1
  :widths: 25 10 65
  
  * - Date
    - Version
    - Title

  * - June 22, 2010
    - B.4
    - WISHBONE System-on-Chip (SoC) Interconnection Architecture for Portable IP Cores
