package com.pxhua.video;

import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.annotation.*;
import com.qq.tars.common.support.Holder;

import com.pxhua.video.proto.httpproto.HttpCGIServant;
import com.pxhua.video.proto.httpproto.st_cgi_req;
import com.pxhua.video.proto.httpproto.st_cgi_rsp;
import com.pxhua.video.proto.account.AccessServant;
import com.pxhua.video.proto.account.st_login_verify_req;
import com.pxhua.video.proto.account.st_login_verify_rsp;

public class AccountServantImpl implements AccessServant {

	@Override
	public void verify(st_login_verify_req req, @TarsHolder Holder<st_login_verify_rsp> rsp){
        System.out.println(req.toString());

		//st_login_verify_rsp verify_rsp = new st_login_verify_rsp();
		rsp.setValue(new st_login_verify_rsp());

		//rsp.value.ret = 100;
		//rsp.value.msg = "message from a CGI server.";
	}
}

