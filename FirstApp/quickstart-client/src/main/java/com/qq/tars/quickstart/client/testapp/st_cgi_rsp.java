// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.0.1.
// **********************************************************************

package com.qq.tars.quickstart.client.testapp;

import com.qq.tars.protocol.util.*;
import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.*;
import com.qq.tars.protocol.tars.annotation.*;

@TarsStruct
public class st_cgi_rsp {

	@TarsStructProperty(order = 0, isRequire = true)
	public int ret = 0;
	@TarsStructProperty(order = 1, isRequire = true)
	public String msg = "";
	@TarsStructProperty(order = 2, isRequire = true)
	public String out_json = "";

	public int getRet() {
		return ret;
	}

	public void setRet(int ret) {
		this.ret = ret;
	}

	public String getMsg() {
		return msg;
	}

	public void setMsg(String msg) {
		this.msg = msg;
	}

	public String getOut_json() {
		return out_json;
	}

	public void setOut_json(String out_json) {
		this.out_json = out_json;
	}

	public st_cgi_rsp() {
	}

	public st_cgi_rsp(int ret, String msg, String out_json) {
		this.ret = ret;
		this.msg = msg;
		this.out_json = out_json;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + TarsUtil.hashCode(ret);
		result = prime * result + TarsUtil.hashCode(msg);
		result = prime * result + TarsUtil.hashCode(out_json);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof st_cgi_rsp)) {
			return false;
		}
		st_cgi_rsp other = (st_cgi_rsp) obj;
		return (
			TarsUtil.equals(ret, other.ret) &&
			TarsUtil.equals(msg, other.msg) &&
			TarsUtil.equals(out_json, other.out_json) 
		);
	}

	public void writeTo(TarsOutputStream _os) {
		_os.write(ret, 0);
		_os.write(msg, 1);
		_os.write(out_json, 2);
	}


	public void readFrom(TarsInputStream _is) {
		this.ret = _is.read(ret, 0, true);
		this.msg = _is.readString(1, true);
		this.out_json = _is.readString(2, true);
	}

}
