package com.example.redditech.utils

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.redditech.R
import com.example.redditech.controllers.SubscribeController
import com.example.redditech.fragments.SubredditFragment

class CustomAdapterSubreddit(private var mList: MutableList<SubRedditItems>) :
    RecyclerView.Adapter<CustomAdapterSubreddit.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.subreddit_card_view, parent, false)
        return ViewHolder(view)
    }

    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val subRedditItems = mList[position]
        if (subRedditItems.image != "")
            Glide.with(holder.imageView.context)
                .load(subRedditItems.image)
                .override(30, 30).fitCenter()
                .into(holder.imageView)
        else
            Glide.with(holder.imageView.context)
                .load(R.drawable.empty_subreddit_image)
                .override(30, 30).fitCenter()
                .into(holder.imageView)
        holder.titleView.text = subRedditItems.title
        holder.descriptionView.text = subRedditItems.description
        if (subRedditItems.userIsSubscribe)
            holder.subscribe.text = "joined"
        else
            holder.subscribe.text = "join"
        holder.subscribe.setOnClickListener {
            if (holder.subscribe.text == "joined") {
                SubscribeController.subToReddit(subRedditItems.title, false)
                holder.subscribe.text = "join"
            } else {
                SubscribeController.subToReddit(subRedditItems.title, true)
                holder.subscribe.text = "joined"
            }
        }
        holder.titleView.text = "r/".plus(subRedditItems.title)
        holder.itemView.setOnClickListener { v: View ->
            val activity = v.context as AppCompatActivity
            val fragmentManager = activity.supportFragmentManager
            DataProvider.subRedditInfo = subRedditItems
            val fragmentTransaction = fragmentManager.beginTransaction()
            fragmentTransaction.replace(R.id.main_fragment, SubredditFragment())
            fragmentTransaction.commit()
            (activity as? AppCompatActivity)?.supportActionBar?.title = holder.titleView.text
        }
    }

    override fun getItemCount() = mList.size

    class ViewHolder(ItemView: View) : RecyclerView.ViewHolder(ItemView) {
        var imageView: ImageView = itemView.findViewById(R.id.image_subreddit)
        var titleView: TextView = itemView.findViewById(R.id.subredditName)
        var descriptionView: TextView = itemView.findViewById(R.id.subredditDescription)
        var subscribe: Button = itemView.findViewById(R.id.subscribeButton)
    }

    fun setData(d: ArrayList<SubRedditItems>) {
        mList = d
    }
}