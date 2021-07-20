function CodeDefine() { 
this.def = new Array();
this.def["ert_main.c:Controller_M_"] = {file: "ert_main_c.html",line:39,type:"var"};
this.def["ert_main.c:Controller_MPtr"] = {file: "ert_main_c.html",line:40,type:"var"};
this.def["ert_main.c:Controller_B"] = {file: "ert_main_c.html",line:41,type:"var"};
this.def["ert_main.c:Controller_DWork"] = {file: "ert_main_c.html",line:42,type:"var"};
this.def["ert_main.c:Controller_U"] = {file: "ert_main_c.html",line:43,type:"var"};
this.def["ert_main.c:Controller_Y"] = {file: "ert_main_c.html",line:44,type:"var"};
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:64,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:101,type:"fcn"};
this.def["rt_roundd"] = {file: "Controller_c.html",line:103,type:"fcn"};
this.def["Controller.c:Controller_blinkBasedOnDistance"] = {file: "Controller_c.html",line:122,type:"fcn"};
this.def["Controller_step"] = {file: "Controller_c.html",line:203,type:"fcn"};
this.def["Controller_initialize"] = {file: "Controller_c.html",line:630,type:"fcn"};
this.def["Controller_terminate"] = {file: "Controller_c.html",line:698,type:"fcn"};
this.def["RT_MODEL_Controller"] = {file: "Controller_h.html",line:31,type:"type"};
this.def["BlockIO_Controller"] = {file: "Controller_h.html",line:41,type:"type"};
this.def["D_Work_Controller"] = {file: "Controller_h.html",line:64,type:"type"};
this.def["ExternalInputs_Controller"] = {file: "Controller_h.html",line:69,type:"type"};
this.def["ExternalOutputs_Controller"] = {file: "Controller_h.html",line:76,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:41,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:42,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:43,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:44,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:45,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:46,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:77,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:82,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:89,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:96,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:103,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:110,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:117,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:124,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:142,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "/";
var isPC = false;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["Controller_c.html"] = "../Controller.c";
	this.html2Root["Controller_c.html"] = "Controller_c.html";
	this.html2SrcPath["Controller_h.html"] = "../Controller.h";
	this.html2Root["Controller_h.html"] = "Controller_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","Controller_c.html","Controller_h.html","rtwtypes_h.html"];
