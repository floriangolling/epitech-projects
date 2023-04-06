package com.example.redditech.models

import org.json.JSONObject

object AccountSettings {
    private var accountData: JSONObject? = null

    fun setData(json: JSONObject) {
        accountData = json
    }

    fun getBadComment(): String? {
        return (accountData!!.optString("bad_comment_autocollapse"))
    }

    fun getProperty(str: String): String {
        if (str == "bad_comment_autocollapse") {
            when {
                accountData!!.optString(str) == "off" -> return ("0")
                accountData!!.optString(str) == "low" -> return ("1")
                accountData!!.optString(str) == "medium" -> return ("2")
                accountData!!.optString(str) == "high" -> return ("3")
            }
        }
        if (str == "accept_pms") {
            when {
                accountData!!.optString(str) == "whitelisted" -> return ("0")
                accountData!!.optString(str) == "everyone" -> return ("1")
            }
        }
        return (accountData!!.optString(str))
    }

    fun setProperty(str: String, value: String) {
        accountData!!.remove(str)
        if (str == "show_presence" ||str == "enable_followers" || str == "email_unsubscribe_all" || str == "show_location_based_recommendations")
                accountData!!.put(str, value.toBoolean())
        else if (str == "accept_pms" || str == "bad_comment_autocollapse") {
            accountData!!.put(str, value)
        }
    }
}