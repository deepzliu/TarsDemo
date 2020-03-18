package com.pxhua.video;

import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.annotation.*;
import com.qq.tars.common.support.Holder;
import com.alibaba.fastjson.JSONObject;
import java.util.List;
import java.util.ArrayList;

import com.pxhua.video.proto.httpproto.HttpCGIServant;
import com.pxhua.video.proto.httpproto.st_cgi_req;
import com.pxhua.video.proto.httpproto.st_cgi_rsp;

public class LoginServantImpl implements HttpCGIServant {

	@Override
	public void get(st_cgi_req cgi_req, Holder<st_cgi_rsp> rsp){
        System.out.println(cgi_req.toString());
		st_cgi_rsp cgi_rsp = new st_cgi_rsp();

		// TODO: config

		// user lock
		// check login from local and wx
		// check if user exist and create if not exist
		// record login cache
		// set cookie

		cgi_rsp.ret = 100;
		cgi_rsp.msg = "message from a CGI server.";

		set_cgi_resp(10025, cgi_rsp);
    	System.out.println("out_json: " + cgi_rsp.out_json);
		rsp.setValue(cgi_rsp);
	}

	private void set_cgi_resp(int ret, st_cgi_rsp rsp)
	{
		JSONObject object = new JSONObject();
    	object.put("ret", ret);
    	object.put("msg", "error msg");

    	//array
    	List<JSONObject> objlist = new ArrayList();
		JSONObject item = new JSONObject();
		item.put("id", 101);
		item.put("name", "Micheal");
		objlist.add(item);
		item.put("id", 102);
		item.put("name", "Noble");
		objlist.add(item);

    	object.put("data",objlist);

		rsp.out_json = object.toJSONString();
	}
}

