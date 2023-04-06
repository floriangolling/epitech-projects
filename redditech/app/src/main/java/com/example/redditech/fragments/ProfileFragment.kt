package com.example.redditech.fragments

import android.os.Build
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.annotation.RequiresApi
import androidx.fragment.app.Fragment
import com.bumptech.glide.Glide
import com.example.redditech.R
import com.example.redditech.models.UserInfo

class ProfileFragment : Fragment() {
    @RequiresApi(Build.VERSION_CODES.O)
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_profile, container, false)
        val prolific: ImageView = view.findViewById(R.id.userProfileImage)
        val url = UserInfo.getProfilePicture()
        val username: TextView = view.findViewById(R.id.profileUsername)
        val description: TextView = view.findViewById(R.id.profileDescription)
        val profileInfo: TextView = view.findViewById(R.id.profileInfo)
        val displayName: TextView = view.findViewById(R.id.displayName)
        val text =
            UserInfo.getProperty("total_karma").plus(" karma • ").plus(UserInfo.getProperty("year"))
                .plus(" y • ").plus(UserInfo.getProperty("created")).plus(" • ")
                .plus(UserInfo.getProperty("subscribers")).plus(" followers")
        Glide.with(this)
            .load(url)
            .override(150, 150)
            .fitCenter()
            .into(prolific)
        username.text = UserInfo.getProperty("name")
        description.text = UserInfo.getProperty("public_description")
        displayName.text = UserInfo.getProperty("display_name")
        profileInfo.text = text
        return view
    }
}