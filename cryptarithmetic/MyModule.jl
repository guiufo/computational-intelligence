#=
    fitness
    Copyright © 2017 guiufo <guiufo@gmail.com>

    Distributed under terms of the MIT license.
=#
module MyModule

export eval

function eval(m)
	for i in 1:180
		send = more = money = 0
		send = m[i,1]*1000+m[i,2]*100+m[i,3]*10+m[i,4]
		more = m[i,5]*1000+m[i,6]*100+m[i,7]*10+m[i,2]
		money = m[i,5]*10000+m[i,6]*1000+m[i,3]*100+m[i,2]*10+m[i,8]
		m[i,end] = abs(send + more - money)
	end
	return m
end

end
