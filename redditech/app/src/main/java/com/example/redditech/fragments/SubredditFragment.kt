package com.example.redditech.fragments

import android.annotation.SuppressLint
import android.graphics.Color
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.redditech.R
import com.example.redditech.controllers.SubredditsHotNewBest
import com.example.redditech.controllers.SubscribeController
import com.example.redditech.models.JSONRedditFormatter
import com.example.redditech.models.SearchSubModels
import com.example.redditech.utils.CustomAdapter
import com.example.redditech.utils.DataProvider
import com.example.redditech.utils.ItemsViewModel
import com.squareup.picasso.Picasso
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class SubredditFragment : Fragment() {
    private var sAdapter: CustomAdapter? = null
    private var data = ArrayList<ItemsViewModel>()
    private lateinit var layout: LinearLayoutManager

    @SuppressLint("ResourceAsColor", "SetTextI18n")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_subreddit, container, false)
        val adapter = ArrayAdapter.createFromResource(
            requireContext(),
            R.array.category_array, android.R.layout.simple_spinner_item
        )
        val categorySpinner: Spinner = view.findViewById(R.id.subreddit_category_spinner)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        categorySpinner.adapter = adapter
        categorySpinner.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            @SuppressLint("NotifyDataSetChanged")
            override fun onItemSelected(adapterView: AdapterView<*>?, view: View, i: Int, l: Long) {
                if (adapterView != null) {
                    val text = adapterView.getItemAtPosition(i).toString()
                    GlobalScope.launch(Dispatchers.IO) {
                        when (text) {
                            "Best" -> {
                                SubredditsHotNewBest.getBestPosts(
                                    DataProvider.subRedditInfo.title,
                                    null
                                )
                                JSONRedditFormatter.formatJson(SearchSubModels.getBestData())
                                DataProvider.currentlyDisplaying = "Best"
                            }
                            "Hot" -> {
                                SubredditsHotNewBest.getHotPosts(
                                    DataProvider.subRedditInfo.title,
                                    null
                                )
                                JSONRedditFormatter.formatJson(SearchSubModels.getHotData())
                                DataProvider.currentlyDisplaying = "Hot"
                            }
                            "New" -> {
                                SubredditsHotNewBest.getNewPosts(
                                    DataProvider.subRedditInfo.title,
                                    null
                                )
                                JSONRedditFormatter.formatJson(SearchSubModels.getNewData())
                                DataProvider.currentlyDisplaying = "New"
                            }
                        }
                        activity!!.runOnUiThread {
                            data.clear()
                            val provider = DataProvider.redditList
                            for (item in provider) {
                                data.add(item)
                            }
                            sAdapter?.setData(data)
                            sAdapter?.notifyDataSetChanged()
                            layout.scrollToPositionWithOffset(0, 0)
                        }
                    }
                }
            }

            override fun onNothingSelected(adapterView: AdapterView<*>?) {
                return
            }
        }
        val recyclerview = view.findViewById<RecyclerView>(R.id.recyclerview_subreddit)
        val subscribers: TextView = view.findViewById(R.id.subscribers_numb)
        val profilePic: ImageView = view.findViewById(R.id.subreddit_profile_pic)
        val joinButton: Button = view.findViewById(R.id.join_button_sub_fragment)
        val description: TextView = view.findViewById(R.id.subreddit_description)
        val banner: ImageView = view.findViewById(R.id.subreddit_banner)
        val titleTitle: TextView = view.findViewById(R.id.title_title)
        recyclerview.layoutManager = LinearLayoutManager(requireContext())
        layout = recyclerview.layoutManager as LinearLayoutManager
        sAdapter = CustomAdapter(data)
        recyclerview.adapter = sAdapter
        titleTitle.text = DataProvider.subRedditInfo.titleTitle
        subscribers.text = DataProvider.subRedditInfo.subscribers.plus(" Members")
        Glide.with(this)
            .load(DataProvider.subRedditInfo.image)
            .override(100, 100)
            .fitCenter()
            .into(profilePic)
        if (DataProvider.subRedditInfo.subreddit_banner != "")
            Picasso.get().load(DataProvider.subRedditInfo.subreddit_banner).fit().centerCrop()
                .into(banner)
        if (DataProvider.subRedditInfo.userIsSubscribe)
            joinButton.text = "joined"
        else
            joinButton.text = "join"
        joinButton.setOnClickListener {
            if (joinButton.text == "joined") {
                SubscribeController.subToReddit(DataProvider.subRedditInfo.title, false)
                joinButton.setBackgroundColor(Color.WHITE)
                joinButton.setTextColor(R.color.subscribe_button)
                joinButton.text = "join"
            } else {
                SubscribeController.subToReddit(DataProvider.subRedditInfo.title, true)
                joinButton.setBackgroundColor(R.color.subscribe_button)
                joinButton.setTextColor(Color.WHITE)
                joinButton.text = "joined"
            }
        }
        description.text = DataProvider.subRedditInfo.description
        return view
    }
}