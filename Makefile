.PHONY: clean All

All:
	@echo "----------Building project:[ seQSim_v2 - Debug ]----------"
	@"$(MAKE)" -f  "seQSim_v2.mk"
clean:
	@echo "----------Cleaning project:[ seQSim_v2 - Debug ]----------"
	@"$(MAKE)" -f  "seQSim_v2.mk" clean
