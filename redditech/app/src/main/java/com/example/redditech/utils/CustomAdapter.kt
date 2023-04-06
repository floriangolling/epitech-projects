package com.example.redditech.utils

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.MediaController
import android.widget.TextView
import android.widget.VideoView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.isVisible
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.redditech.R
import com.example.redditech.controllers.SubredditsHotNewBest
import com.example.redditech.controllers.UserSubreddits
import com.example.redditech.models.JSONRedditFormatter
import com.example.redditech.models.SearchSubModels
import com.example.redditech.models.UserSubredditsModel
import io.github.ponnamkarthik.richlinkpreview.RichLinkViewTelegram
import io.github.ponnamkarthik.richlinkpreview.ViewListener
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch

class CustomAdapter(private var mList: MutableList<ItemsViewModel>) :
    RecyclerView.Adapter<CustomAdapter.ViewHolder>() {

    private lateinit var playerView: VideoView
    private lateinit var myView: View
    private var videoUrl: String = ""

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.card_view_design, parent, false)
        myView = view
        playerView = view.findViewById(R.id.videoPlayer_card)
        return ViewHolder(view)
    }

    @SuppressLint("NotifyDataSetChanged")
    override fun onBindViewHolder(holder: ViewHolder, position: Int) {

        val itemsViewModel = mList[position]
        holder.titleView.text = itemsViewModel.title
        holder.textView.isVisible = false
        holder.imageView.isVisible = false
        holder.videoView.isVisible = false
        holder.linkView.isVisible = false
        when (itemsViewModel.cardType) {
            CardTypeEnum.TEXT -> {
                holder.textView.text = itemsViewModel.text
                holder.textView.isVisible = true
            }
            CardTypeEnum.IMAGE -> {
                Glide.with(holder.imageView.context)
                    .load(itemsViewModel.link)
                    .into(holder.imageView)
                holder.imageView.isVisible = true
            }
            CardTypeEnum.GIF -> {
                Glide.with(holder.imageView.context)
                    .asGif()
                    .load(itemsViewModel.link)
                    .into(holder.imageView)
                holder.imageView.isVisible = true
            }
            CardTypeEnum.LINK -> {
                holder.linkView.setLink(itemsViewModel.link, object : ViewListener {
                    override fun onSuccess(status: Boolean) {
                    }

                    override fun onError(e: Exception) {
                    }
                })
                holder.linkView.isVisible = true
            }
            CardTypeEnum.VIDEO -> {
                videoUrl = itemsViewModel.link
                if (itemsViewModel.videoType == VideoTypeHost.HOSTED || itemsViewModel.videoType == VideoTypeHost.RICH) {
                    val mediaController = MediaController(holder.videoView.context)
                    mediaController.setAnchorView(holder.videoView)
                    holder.videoView.setVideoPath(videoUrl)
                    holder.videoView.seekTo(1)
                    holder.videoView.setMediaController(mediaController)
                    holder.videoView.requestFocus()
                }
                holder.videoView.isVisible = true
            }
            CardTypeEnum.EMPTY -> {
                println("empty")
            }
        }
        holder.username.text = itemsViewModel.Username
        holder.subreddit.text = itemsViewModel.subreddit
        holder.likesNumber.text = itemsViewModel.likeNumber.toString()
        holder.commentsNumber.text = itemsViewModel.commentsNumber.toString()

        if (position == itemCount - 1) {
            GlobalScope.launch(Dispatchers.IO) {
                if (DataProvider.onPage == "main") {
                    when (DataProvider.currentlyDisplaying) {
                        "Best" -> {
                            UserSubreddits.getBestPosts(DataProvider.afterName)
                            JSONRedditFormatter.formatJson(UserSubredditsModel.getBestData())
                        }
                        "New" -> {
                            UserSubreddits.getNewPost(DataProvider.afterName)
                            JSONRedditFormatter.formatJson(UserSubredditsModel.getNewData())
                        }
                        "Hot" -> {
                            UserSubreddits.getHotPost(DataProvider.afterName)
                            JSONRedditFormatter.formatJson(UserSubredditsModel.getHotData())
                        }
                    }
                } else if (DataProvider.onPage == "sub") {
                    when (DataProvider.currentlyDisplaying) {
                        "Best" -> {
                            SubredditsHotNewBest.getBestPosts(
                                DataProvider.subRedditInfo.title,
                                DataProvider.afterName
                            )
                            JSONRedditFormatter.formatJson(SearchSubModels.getBestData())
                        }
                        "New" -> {
                            SubredditsHotNewBest.getNewPosts(
                                DataProvider.subRedditInfo.title,
                                DataProvider.afterName
                            )
                            JSONRedditFormatter.formatJson(SearchSubModels.getNewData())
                        }
                        "Hot" -> {
                            SubredditsHotNewBest.getHotPosts(
                                DataProvider.subRedditInfo.title,
                                DataProvider.afterName
                            )
                            JSONRedditFormatter.formatJson(SearchSubModels.getHotData())
                        }
                    }
                }
                val activity = myView.context as AppCompatActivity
                activity.runOnUiThread {
                    mList.clear()
                    for (i in DataProvider.redditList) {
                        mList.add(i)
                    }
                    notifyDataSetChanged()
                }
            }
        }
    }

    override fun getItemCount() = mList.size

    class ViewHolder(ItemView: View) : RecyclerView.ViewHolder(ItemView) {
        val imageView: ImageView = itemView.findViewById(R.id.imageView_card)
        val titleView: TextView = itemView.findViewById(R.id.titleView_card)
        val textView: TextView = itemView.findViewById(R.id.textView_card)
        val linkView: RichLinkViewTelegram = itemView.findViewById(R.id.previewLinkView_card)
        val videoView: VideoView = itemView.findViewById(R.id.videoPlayer_card)
        val username: TextView = itemView.findViewById(R.id.userNameCard)
        val subreddit: TextView = itemView.findViewById(R.id.subredditName)
        val commentsNumber: TextView = itemView.findViewById(R.id.numberOfComments)
        val likesNumber: TextView = itemView.findViewById(R.id.numberOfLikes)
    }

    fun setData(d: ArrayList<ItemsViewModel>) {
        mList = d
    }
}

