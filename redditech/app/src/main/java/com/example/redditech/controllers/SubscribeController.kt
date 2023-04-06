package com.example.redditech.controllers

import android.content.ContentValues
import android.util.Log
import com.example.redditech.oauth.OAuthManager
import okhttp3.*
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object SubscribeController {
    fun subToReddit(value : String, sub: Boolean) {
        val obj = JSONObject()
        if (sub)
            obj.put("action", "sub")
        else if (!sub)
            obj.put("action", "unsub")
        obj.put("sr_name", value)
        val countDownLatch = CountDownLatch(1)

        val request2 = FormBody.Builder()
            .add("sr_name", value)
            .add("action", obj.optString("action"))
            .build()

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Bearer ${OAuthManager.getAccessToken().toString()}")
            .url("https://oauth.reddit.com/api/subscribe")
            .post(request2)
            .build()

        NetworkManager.getClient().newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(ContentValues.TAG, "ERROR: $e")
                countDownLatch.countDown()
            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                try {
                    countDownLatch.countDown()
                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()
                }
            }
        })
        countDownLatch.await()
    }
}