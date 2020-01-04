// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.0.1.
// **********************************************************************

package com.qq.tars.quickstart.client.testapp;

import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.annotation.*;
import com.qq.tars.common.support.Holder;

@Servant
public interface CGIPrx {

	public int get(st_cgi_req cgi_req, st_cgi_rsp cgi_rsp);

	public int get(st_cgi_req cgi_req, st_cgi_rsp cgi_rsp, @TarsContext java.util.Map<String, String> ctx);

	public void async_get(@TarsCallback CGIPrxCallback callback, st_cgi_req cgi_req, st_cgi_rsp cgi_rsp);

	public void async_get(@TarsCallback CGIPrxCallback callback, st_cgi_req cgi_req, st_cgi_rsp cgi_rsp, @TarsContext java.util.Map<String, String> ctx);
}
