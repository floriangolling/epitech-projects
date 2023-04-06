package com.example.redditech.fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.preference.ListPreference
import androidx.preference.PreferenceFragmentCompat
import androidx.preference.SwitchPreference
import com.example.redditech.R
import com.example.redditech.controllers.AccountPatch
import com.example.redditech.controllers.AccountSettingsGet
import com.example.redditech.models.AccountSettings

class SettingsFragment : PreferenceFragmentCompat() {

    override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
        setPreferencesFromResource(R.xml.preferences, rootKey)
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        var switch: SwitchPreference? = findPreference("enable_followers")
        switch?.setOnPreferenceClickListener {
            var bool = AccountSettings.getProperty("enable_followers").toBoolean()
            bool = !bool
            AccountSettings.setProperty("enable_followers", bool.toString())
            AccountPatch.enableFollower(AccountSettings.getProperty("enable_followers").toBoolean())
            true
        }
        switch = findPreference("show_location_based_recommendations")
        switch?.setOnPreferenceClickListener {
            var bool =
                AccountSettings.getProperty("show_location_based_recommendations").toBoolean()
            bool = !bool
            AccountSettings.setProperty("show_location_based_recommendations", bool.toString())
            AccountPatch.showRecommendationGeo(
                AccountSettings.getProperty("show_location_based_recommendations").toBoolean()
            )
            true
        }
        switch = findPreference("email_unsubscribe_all")
        switch?.setOnPreferenceClickListener {
            var bool = AccountSettings.getProperty("email_unsubscribe_all").toBoolean()
            bool = !bool
            AccountSettings.setProperty("email_unsubscribe_all", bool.toString())
            AccountPatch.unsubscribeMail(
                AccountSettings.getProperty("email_unsubscribe_all").toBoolean()
            )
            true
        }
        val listValue: ListPreference? = findPreference("bad_comment_autocollapse")
        listValue?.setOnPreferenceChangeListener { _, newValue ->
            when (newValue.toString()) {
                "0" -> {
                    AccountSettings.setProperty("bad_comment_autocollapse", "off")
                }
                "1" -> {
                    AccountSettings.setProperty("bad_comment_autocollapse", "low")
                }
                "2" -> {
                    AccountSettings.setProperty("bad_comment_autocollapse", "medium")
                }
                "3" -> {
                    AccountSettings.setProperty("bad_comment_autocollapse", "high")
                }
            }
            AccountPatch.badCommentAutoCollapse(AccountSettings.getBadComment().toString())
            true
        }
        val secondList: ListPreference? = findPreference("accept_pm")
        secondList?.setOnPreferenceChangeListener { _, newValue ->
            if (newValue.toString() == "0") {
                AccountSettings.setProperty("accept_pms", "whitelisted")
                AccountPatch.acceptPms("whitelisted")
            } else if (newValue.toString() == "1") {
                AccountSettings.setProperty("accept_pms", "everyone")
                AccountPatch.acceptPms("everyone")
            }
            true
        }
        return super.onCreateView(inflater, container, savedInstanceState)
    }

    override fun onResume() {
        super.onResume()
        AccountSettingsGet.getSettingsInfo()
        var switch: SwitchPreference? = findPreference("enable_followers")
        if (switch != null) {
            switch.isChecked = AccountSettings.getProperty("enable_followers").toBoolean()
        }
        switch = findPreference("show_location_based_recommendations")
        if (switch != null) {
            switch.isChecked =
                AccountSettings.getProperty("show_location_based_recommendations").toBoolean()
        }
        switch = findPreference("email_unsubscribe_all")
        if (switch != null) {
            switch.isChecked = AccountSettings.getProperty("email_unsubscribe_all").toBoolean()
        }
        var listValue: ListPreference? = findPreference("bad_comment_autocollapse")
        listValue?.setValueIndex(AccountSettings.getProperty("bad_comment_autocollapse").toInt())
        listValue = findPreference("accept_pm")
        listValue?.setValueIndex(AccountSettings.getProperty("accept_pms").toInt())
    }

}

