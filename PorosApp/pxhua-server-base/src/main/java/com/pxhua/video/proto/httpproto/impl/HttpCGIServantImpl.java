package com.pxhua.video.proto.httpproto.impl;

import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.annotation.*;
import com.qq.tars.common.support.Holder;

import com.pxhua.video.proto.httpproto.HttpCGIServant;
import com.pxhua.video.proto.httpproto.st_cgi_req;
import com.pxhua.video.proto.httpproto.st_cgi_rsp;

public class HttpCGIServantImpl implements HttpCGIServant {

	@Override
	public void get(st_cgi_req cgi_req, Holder<st_cgi_rsp> rsp){
        System.out.println(cgi_req.toString());

		st_cgi_rsp cgi_rsp = new st_cgi_rsp();
		rsp.setValue(cgi_rsp);

		rsp.value.ret = 100;
		rsp.value.msg = "message from base server.";
	}
}

