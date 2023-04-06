package com.example.redditech.activity

import android.content.ContentValues.TAG
import android.content.Context
import android.content.Intent
import android.content.SharedPreferences
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.ProgressBar
import android.widget.TextView
import com.example.redditech.R
import com.example.redditech.controllers.AccountSettingsGet
import com.example.redditech.controllers.NetworkManager
import com.example.redditech.controllers.User
import com.example.redditech.oauth.OAuthManager
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class LoginActivity : AppCompatActivity() {
    private var progressBar: ProgressBar? = null
    private var buttonLogin: Button? = null
    private var textLogin : TextView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)
        val button = findViewById<Button>(R.id.button)
        textLogin = findViewById(R.id.Connection)
        progressBar = findViewById(R.id.progress_Bar)
        buttonLogin = button
        button.setOnClickListener{
            startSigning()
        }
        val p :SharedPreferences = getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
        val token : String? = p.getString("TOKEN", null)
        if (token != null && token != "" && token != "null") {
            GlobalScope.launch(Dispatchers.IO) {
                runOnUiThread {
                    textLogin!!.visibility = View.VISIBLE
                    button.visibility = View.INVISIBLE
                    progressBar!!.visibility = View.VISIBLE
                }
                OAuthManager.getAccessTokenUsingRefresh(token, NetworkManager.getClient())
                User.getClientInfo()
                AccountSettingsGet.getSettingsInfo()
                val intent = Intent(this@LoginActivity, MainActivity::class.java)
                startActivity(intent)
            }
        } else {
            progressBar!!.visibility = View.INVISIBLE
            button.visibility = View.VISIBLE
            textLogin!!.visibility = View.INVISIBLE
        }
    }

    private fun startSigning() {
        val string = OAuthManager.getOauthLink()
        val intent = Intent(Intent.ACTION_VIEW, Uri.parse(string))
        startActivity(intent)
    }

    override fun onResume() {
        super.onResume()
        progressBar!!.visibility = View.INVISIBLE
        buttonLogin!!.visibility = View.VISIBLE
        textLogin!!.visibility = View.INVISIBLE
        if (intent != null && intent.action == Intent.ACTION_VIEW) {
            val uri = intent.data
            if (uri!!.getQueryParameter("error") != null) {
                val error = uri.getQueryParameter("error")
                Log.e(TAG, "An error has occurred : $error")
            } else {
                val state = uri.getQueryParameter("state")
                if (state == OAuthManager.getState()) {
                    val code = uri.getQueryParameter("code").toString()
                    GlobalScope.launch(Dispatchers.IO) {
                        runOnUiThread {
                            progressBar!!.visibility = View.VISIBLE
                            buttonLogin!!.visibility = View.INVISIBLE
                            textLogin!!.visibility = View.VISIBLE
                        }
                        OAuthManager.getAccessToken(code, NetworkManager.getClient())
                        val p: SharedPreferences =
                            getSharedPreferences("MY_APP", Context.MODE_PRIVATE)
                        p.edit().putString("TOKEN", OAuthManager.getRefreshToken().toString())
                            .apply()
                        Log.d(TAG, "token :${OAuthManager.getAccessToken()}")
                        User.getClientInfo()
                        AccountSettingsGet.getSettingsInfo()
                        val intent = Intent(this@LoginActivity, MainActivity::class.java)
                        startActivity(intent)
                    }
                }
            }
        }
    }
}