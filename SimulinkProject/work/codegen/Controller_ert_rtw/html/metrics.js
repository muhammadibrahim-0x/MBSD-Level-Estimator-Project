function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Controller.c:Controller_blinkBasedOnDistance"] = {file: "/Users/moody/My Files/Polito/ThirdYear/MBSD/New/SimulinkProject/work/codegen/Controller_ert_rtw/Controller.c",
	stack: 8,
	stackTotal: 16};
	 this.metricsArray.fcn["Controller_initialize"] = {file: "/Users/moody/My Files/Polito/ThirdYear/MBSD/New/SimulinkProject/work/codegen/Controller_ert_rtw/Controller.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["Controller_step"] = {file: "/Users/moody/My Files/Polito/ThirdYear/MBSD/New/SimulinkProject/work/codegen/Controller_ert_rtw/Controller.c",
	stack: 12,
	stackTotal: 28};
	 this.metricsArray.fcn["Controller_terminate"] = {file: "/Users/moody/My Files/Polito/ThirdYear/MBSD/New/SimulinkProject/work/codegen/Controller_ert_rtw/Controller.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["ceil"] = {file: "/Applications/MATLAB_R2020b.app/polyspace/verifier/cxx/include/include-libc/bits/mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabs"] = {file: "/Applications/MATLAB_R2020b.app/polyspace/verifier/cxx/include/include-libc/bits/mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["floor"] = {file: "/Applications/MATLAB_R2020b.app/polyspace/verifier/cxx/include/include-libc/bits/mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "/Applications/MATLAB_R2020b.app/polyspace/verifier/cxx/include/include-libc/string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rt_roundd"] = {file: "/Users/moody/My Files/Polito/ThirdYear/MBSD/New/SimulinkProject/work/codegen/Controller_ert_rtw/Controller.c",
	stack: 8,
	stackTotal: 8};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="Controller_metrics.html">Global Memory: 0(bytes) Maximum Stack: 12(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
