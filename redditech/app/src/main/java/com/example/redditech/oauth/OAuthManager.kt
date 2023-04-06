package com.example.redditech.oauth

import android.content.ContentValues.TAG
import android.util.Base64
import android.util.Log
import okhttp3.*
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import okhttp3.RequestBody.Companion.toRequestBody
import org.json.JSONException
import org.json.JSONObject
import java.io.IOException
import java.util.concurrent.CountDownLatch

object OAuthManager {
    private var access_token: String? = null
    private var refresh_token: String? = null
    private var token: String? = null
    private const val CLIENT_ID: String = "cZ9dWEfdQU8l4WJJJMc4ig"
    private const val MY_STATE: String = "MY_RANDOM_STRING_2"
    private const val REDIRECT_URI: String = "http://www.example.com/my_redirect"

    fun getAccessTokenUsingRefresh(code: String, client: OkHttpClient) {

        val countDownLatch = CountDownLatch(1)

        val authString = "$CLIENT_ID:"
        val encodedAuthString = Base64.encodeToString(authString.toByteArray(), Base64.NO_WRAP)

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Basic $encodedAuthString")
            .url("https://www.reddit.com/api/v1/access_token")
            .post(
                "grant_type=refresh_token&refresh_token=$code"
                    .toRequestBody("application/x-www-form-urlencoded".toMediaTypeOrNull())
            )
            .build()

        client.newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(TAG, "ERROR: $e")
                countDownLatch.countDown()

            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                val json = response.body!!.string()
                try {
                    val data = JSONObject(json)
                    setAccessToken(data.optString("access_token"))
                    countDownLatch.countDown()

                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()

                }
            }
        })
        countDownLatch.await()
    }

    fun getOauthLink(): String {
        val string = String.format(
            "https://www.reddit.com/api/v1/authorize.compact?client_id=%s" + "&response_type=code&state=%s&redirect_uri=%s&" + "duration=permanent&scope=%s",
            CLIENT_ID,
            MY_STATE,
            REDIRECT_URI,
            "read,identity,account,subscribe"
        )
        return (string)
    }

    fun getState(): String {
        return MY_STATE
    }

    fun getAccessToken(code: String, client: OkHttpClient) {

        setToken(code)
        val countDownLatch = CountDownLatch(1)

        val authString = "$CLIENT_ID:"
        val encodedAuthString = Base64.encodeToString(authString.toByteArray(), Base64.NO_WRAP)

        val request: Request = Request.Builder()
            .addHeader("User-Agent", "Sample app")
            .addHeader("Authorization", "Basic $encodedAuthString")
            .url("https://www.reddit.com/api/v1/access_token")
            .post(
                ("grant_type=authorization_code&code=" + getToken().toString() +
                        "&redirect_uri=" + "http://www.example.com/my_redirect"
                        ).toRequestBody("application/x-www-form-urlencoded".toMediaTypeOrNull())
            )
            .build()

        client.newCall(request).enqueue(object : Callback {
            override fun onFailure(call: Call, e: IOException) {
                Log.e(TAG, "ERROR: $e")
                countDownLatch.countDown()

            }

            @Throws(IOException::class)
            override fun onResponse(call: Call, response: Response) {
                val json = response.body!!.string()
                try {
                    val data = JSONObject(json)
                    setAccessToken(data.optString("access_token"))
                    setRefreshToken(data.optString("refresh_token"))
                    countDownLatch.countDown()

                } catch (e: JSONException) {
                    e.printStackTrace()
                    countDownLatch.countDown()

                }
            }
        })
        countDownLatch.await()
    }

    private fun getToken(): String? {
        return (token)
    }

    private fun setToken(t: String) {
        token = t
    }

    fun setAccessToken(t: String) {
        access_token = t
    }

    fun getAccessToken(): String? {
        return access_token
    }

    fun setRefreshToken(t: String) {
        refresh_token = if (t == "")
            null
        else
            t
    }

    fun getRefreshToken(): String? {
        return refresh_token
    }
}