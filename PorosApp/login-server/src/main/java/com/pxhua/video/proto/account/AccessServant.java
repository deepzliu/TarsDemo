// **********************************************************************
// This file was generated by a TARS parser!
// TARS version 1.0.1.
// **********************************************************************

package com.pxhua.video.proto.account;

import com.qq.tars.protocol.annotation.*;
import com.qq.tars.protocol.tars.annotation.*;
import com.qq.tars.common.support.Holder;

@Servant
public interface AccessServant {

	public void verify(st_login_verify_req req, @TarsHolder Holder<st_login_verify_rsp> rsp);
}
