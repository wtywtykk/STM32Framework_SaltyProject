transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/PortController.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/FSMCController.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/EdgeDetector.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/FreqDivider.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/PeripBridgeTypes.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/ParPortController.vhd}
vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/PeripheralBridge.vhd}

vcom -93 -work work {F:/WorkDir/EleProjects/SaltyProject/PeripheralBridge_NotEnoughSalt/simulation/modelsim/PeripheralBridge.vht}

vsim -t 1ps -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L maxii -L rtl_work -L work -voptargs="+acc"  TB

add wave *
view structure
view signals
run -all
